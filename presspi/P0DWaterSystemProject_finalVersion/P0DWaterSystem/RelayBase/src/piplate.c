/** 
 * Copyright (c) 2016 Clark McGrew 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. 
 */

#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include <bcm2835.h>

#include "piplate.h"

/** The known plate addresses. */
enum {
     PIPLATE_MOTOR_BASE_ADDRESS = 16,
     PIPLATE_RELAY_BASE_ADDRESS = 24,
     PIPLATE_MAX_PLATE_ADDRESS = 255,
};

/** The BCM GPIO lines being used */
enum {
     /* The output GPIO that is used to control the frame on the pi-plates.
      * When this line is set, the pi-plates are ready for communication over
      * SPI.  When this transitions from false to true, the SPI communications
      * are reset. */
     PIPLATE_FRAME_CONTROL_GPIO = 25,

     /* The input GPIO used by the pi-plates.  The process can set an
      * interrupt on the falling edge. */
     PIPLATE_INTERRUPT_INPUT_GPIO = 22
};
     
/** The commands that can be sent to the pi-plates */
enum {
     /* Commands supported by all boards */
     PIPLATE_CMD_POLL                 = 0x00,
     PIPLATE_CMD_GET_ID               = 0x01,
     PIPLATE_CMD_GET_HW_REVISION      = 0x02,
     PIPLATE_CMD_GET_FW_REVISION      = 0x03,
     /* Commands for the relay board */
     PIPLATE_CMD_RELAY_ON             = 0x10,
     PIPLATE_CMD_RELAY_OFF            = 0x11,
     PIPLATE_CMD_RELAY_TOGGLE         = 0x12,
     PIPLATE_CMD_RELAY_MASK           = 0x13,
     PIPLATE_CMD_RELAY_STATE          = 0x14,
     /* Low level LED control commands */
     PIPLATE_CMD_LED_ON               = 0x60,
     PIPLATE_CMD_LED_OFF              = 0x61,
     PIPLATE_CMD_LED_TOGGLE           = 0x62,
};

/* The amount of time that the pi-plate takes to respond (in microseconds).
 * This will use nanosleep, which has a minimum (realistic) delay of ~200
 * microseconds.  Delays less than that will tend to be about 200
 * microseconds.  This is defined so it can be overridden during the
 * compilation */
#ifndef PIPLATE_RESPONSE_DELAY
#define PIPLATE_RESPONSE_DELAY 1000
#endif

/* The SPI device used to communicate with the pi-plates.  The device file
 * must have appropriate permissions to allow the user to read and write to
 * it. This is defined so it can be overridden during the compilation*/
#ifndef PIPLATE_SPI_DEVICE
#define PIPLATE_SPI_DEVICE "/dev/spidev0.1"
#endif

/** An array of flags for the plate addresses that are found to be occupied.
 * The address is one byte, and is unique to the type of board. */
static int piplatePresent[PIPLATE_MAX_PLATE_ADDRESS];

/** A convenient wrapper around nanosleep. */
static void piplate_delay(int micro) {
     nanosleep((const struct timespec[]){0,micro*1000},NULL);
}

/* Check that there is a plate that was found at the requested address.  The
 * address is 0 to 255.  This returns non-zero if the plate is valid. */
static int valid_plate_address(int addr) {
     if (addr<0) return 0;
     if (PIPLATE_MAX_PLATE_ADDRESS <= addr) return 0;
     return piplatePresent[addr];
}

/* Check that a valid relay connector has been requested. */
static int valid_relay_number(int num) {
     if (num<1) return 0;//changed by Yue, it was "if(num<0)"
     if (num>7) return 0;
     return -1;
}

/* Send a command over SPI to the a pi-plate.  The addr is between 0 and 255.
 * The commands are defined in an enum above.  This returns the number of
 * bytes read from the SPI device, or a negative value if there is an error.
 * This uses the spidev interface, and opens the device file on every call. */
static int piplate_command(int addr, int command, int arg1, int arg2,
                           char* buf, size_t size) {
     
     if (addr<0 || 255<addr) return -1;
     if (size>0) memset(buf,0,size);

     int piplate_spi_fd = open(PIPLATE_SPI_DEVICE,O_RDWR);
     if (piplate_spi_fd < 0) return piplate_spi_fd;
     
     piplate_delay(PIPLATE_RESPONSE_DELAY);
     bcm2835_gpio_set(PIPLATE_FRAME_CONTROL_GPIO);

     char args[4];
     args[0] = addr;
     args[1] = command;
     args[2] = arg1;
     args[3] = arg2;

     piplate_delay(PIPLATE_RESPONSE_DELAY);
     if (write(piplate_spi_fd,args,4) != 4) {
          close(piplate_spi_fd);
          return -1;
     }

     int count = 0;
     while (count<size) {
          char dummy;
          piplate_delay(PIPLATE_RESPONSE_DELAY);
          int status = read(piplate_spi_fd,&dummy,1);
          if (status != 1) {
               close(piplate_spi_fd);
               return -1;
          }
          buf[count++] = dummy;
     }
     
     piplate_delay(PIPLATE_RESPONSE_DELAY);
     bcm2835_gpio_clr(PIPLATE_FRAME_CONTROL_GPIO);

     close(piplate_spi_fd);

     return size;
}

int piplate_relay_address(int address) {
     if (address<0) return -1;
     if (address>7) return -1;
     int addr = address + PIPLATE_RELAY_BASE_ADDRESS;
     if (!valid_plate_address(addr)) {
			printf("!valid_plate_address" );
          return -1;
     }
     return addr;
}

int piplate_init() {
     /* The user must have read/write permission for /dev/gpiomem (or
      * /dev/mem), and /dev/spidev0.1 (i.e. PIPLATE_SPI_DEVICE) */
     return piplate_init_interrupt(0);
}

int piplate_init_interrupt(int enableInterrupt) {
     /* Do the real work to initialize the piplate.  If enable enableInterrupt
      * is non-zero, the this will to setup the interrupt.  The user must have
      * read/write permission for /dev/gpiomem (or /dev/mem), and
      * /dev/spidev0.1 (i.e. PIPLATE_SPI_DEVICE).  If the interrupt is
      * enabled, the permission is required for /dev/mem. */
     if (!bcm2835_init()) return -1;
     

     /* Set up the frame control pin */
     piplate_delay(PIPLATE_RESPONSE_DELAY);
     bcm2835_gpio_fsel(PIPLATE_FRAME_CONTROL_GPIO,BCM2835_GPIO_FSEL_OUTP);

     /* Set it to low which will force the pi-plate to put it's SPI engine
      * into a known state. */
     piplate_delay(PIPLATE_RESPONSE_DELAY);
     bcm2835_gpio_clr(PIPLATE_FRAME_CONTROL_GPIO);
     
     /* Allow time for the pi-plate to reset its SPI engine (if necessary) */
     piplate_delay(PIPLATE_RESPONSE_DELAY);
     
     /* Set up the optional interrupt pin */
     if (enableInterrupt) {
          if (bcm2835_peripherals_base && bcm2835_gpio) {
               bcm2835_gpio_fsel(PIPLATE_INTERRUPT_INPUT_GPIO,
                                 BCM2835_GPIO_FSEL_INPT);
               piplate_delay(PIPLATE_RESPONSE_DELAY);
               bcm2835_gpio_set_pud(PIPLATE_INTERRUPT_INPUT_GPIO,
                                    BCM2835_GPIO_PUD_UP);
               piplate_delay(PIPLATE_RESPONSE_DELAY);
          }
          else {
               printf("WARNING: " __FILE__ ": %s\n","Interrupt not enabled.");
          }
     }
     
     int addr;
     for (addr=0; addr<PIPLATE_MAX_PLATE_ADDRESS; ++addr) {
          piplatePresent[addr] = 0;
     }

     /* Check all of the addresses for boards */
     char response[32];
     for (addr=0; addr<PIPLATE_MAX_PLATE_ADDRESS; ++addr) {
          if (piplate_command(addr,PIPLATE_CMD_POLL,0,0,response,1)<0) {
               return -1;
          }
          if (response[0] != 0) piplatePresent[addr] = -1;
     }

     return 0;
}

void piplate_close() {
     int i;
     for (i=0; i<PIPLATE_MAX_PLATE_ADDRESS; ++i) {
          piplatePresent[i] = 0;
     }
     bcm2835_close();
}

int piplate_name(int addr, void* buf, int nbuf) {
     if (nbuf>0) memset(buf,0,nbuf);
     if (!valid_plate_address(addr)) return -1;

     char response[32];
     memset(response,0,sizeof(response));
     if (piplate_command(addr,PIPLATE_CMD_GET_ID,0,0,response,20)<0) {
          return -1;
     }

     if (nbuf>1) strncpy(buf,response,nbuf);
     *(((char*)buf)+nbuf-1) = 0; /* Make sure it's zero terminated... */

     return strnlen(buf,nbuf);
}

float piplate_hardware(int addr) {
     if (!valid_plate_address(addr)) {
          return -1.0;
     }
     char response;
     if (piplate_command(addr,PIPLATE_CMD_GET_HW_REVISION,
                         addr,0,&response,1)<0) {
          return -1;
     }
     int whole = response>>4;
     int point = response & 0x0f;
     return ((float) whole)+0.1*((float) point);
}

float piplate_firmware(int addr) {
     if (!valid_plate_address(addr)) {
          return -1.0;
     }
     char response;
     if (piplate_command(addr,PIPLATE_CMD_GET_FW_REVISION,
                         addr,0,&response,1)<0) {
          return -1.0;
     }
     int whole = response>>4;
     int point = response & 0x0f;
     return ((float) whole)+0.1*((float) point);
}

int piplate_relay_available(int addr) {
     addr = piplate_relay_address(addr);
     if (addr<0) return 0;
     return -1;
}

int piplate_relay_on(int address, int relay) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(relay)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_RELAY_ON,relay,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_off(int address, int relay) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(relay)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_RELAY_OFF,relay,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_toggle(int address, int relay) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(relay)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_RELAY_TOGGLE,relay,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_mask(int address, int mask) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (mask<0) return -1;
     if (127<mask) return -1;
     if (piplate_command(addr,PIPLATE_CMD_RELAY_MASK,mask,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_state(int address) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     char response;
     if (piplate_command(addr,PIPLATE_CMD_RELAY_STATE,0,0,&response,1)<0) {
          return -1;
     }
     return response;
}

int piplate_relay_led_on(int address, int led) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(led)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_LED_ON,led,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_led_off(int address, int led) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(led)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_LED_OFF,led,0,NULL,0)<0) {
          return -1;
     }
     return address;
}

int piplate_relay_led_toggle(int address, int led) {
     int addr = piplate_relay_address(address);
     if (addr<0) return -1;
     if (!valid_relay_number(led)) return -1;
     if (piplate_command(addr,PIPLATE_CMD_LED_TOGGLE,led,0,NULL,0)<0) {
          return -1;
     }
     return address;
}
