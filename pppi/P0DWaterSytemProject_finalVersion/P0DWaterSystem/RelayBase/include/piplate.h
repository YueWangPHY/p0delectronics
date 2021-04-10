#ifndef relayPLATE_h_Seen
#define relayPLATE_h_Seen
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

#ifdef __cplusplus
extern "C" {
#endif

     /** Initialize the interfaces for any pi-plate.  The user must have
      * read/write permission for /dev/gpiomem (or /dev/mem), and
      * /dev/spidev0.1 (a.k.a. PIPLATE_SPI_DEVICE).  This can be done by
      * either using the root uid, or by appropriately setting the user
      * groups.  On error, this returns a negative value. */
     int piplate_init(void);

     /** Initialize the interfaces for any pi-plate and setup the optional
      * interrupt control line.  If enableInterrupt is zero, the interrupt is
      * NOT setup.  The user must have read/write permission to /dev/mem to
      * enable the interrupt (usually reserved for UID 0), othersize
      * permission for /dev/gpiomem is sufficient.  This requires read/write
      * access to /dev/spidev0.1 (a.k.a. PIPLATE_SPI_DEVICE).  On error, this
      * returns a negative value. */
     int piplate_init_interrupt(int enableInterrupt);

     /** Close the piplates interface. */
     void piplate_close(void);

     /** Get the name of a plate at a particular address.  The address is
      * calculated relative to the base address for a particular type of
      * plate.  For instance, a MOTORplate has a base address of 16.  The
      * first MOTORplate will be at address 16, the second, at 17, and so on.
      * This returns the the number of returned characters, or a negative
      * number if there is an error.  It is primarily an internal
      * function.  */
     int piplate_name(int addr, void* buf, int nbuf);

     /** Get the hardware revision for a plate at a particular address.  The
      * address is calculated relative to the base address for a particular
      * type of plate.  For instance, a MOTORplate has a base address of 16.
      * The first MOTORplate will be at address 16, the second, at 17, and so
      * on.  This returns the hardware version as a floating point number, or
      * a netagive value if there is an error. */
     float piplate_hardware(int addr);

     /** Get the firmware revision for a plate at a particular address.  The
      * address is calculated relative to the base address for a particular
      * type of plate.  For instance, a MOTORplate has a base address of 16.
      * The first MOTORplate will be at address 16, the second, at 17, and so
      * on.  This returns the firmware version as a floating point number, or
      * a negative value if there is an error. */
     float piplate_firmware(int addr);

     /** Translate a relay address (0 to 7) into a global address (0 to 255).
      * The global address can be used with piplate_name, piplate_hardware,
      * and piplate_firmware.  This returns a negative number if the relay
      * address is invalid. */
     int piplate_relay_address(int address);
     
     /** Non-zero if there is a working relay board at the queried relay
      * address.  The relay address is from 0 to 7. */
     int piplate_relay_available(int address);

     /** Turn a relay on.  The address is from 0 to 7, and the relay number is
      * 1 to 7.  This returns the relay board number if successful, or a
      * negative number if there is an error. */
     int piplate_relay_on(int address, int relay);
     
     /** Turn a relay off.  The address is from 0 to 7, and the relay number
      * is 1 to 7.  This returns the relay board number if successful, or a
      * negative number if there is an error. */
     int piplate_relay_off(int address, int relay);

     /** Toggle the state of a relay.  The address is from 0 to 7, and the
      * relay number is 1 to 7. This returns the relay board number on
      * success, or a negative number if there is an error. */
     int piplate_relay_toggle(int address, int relay);

     /** Set the relay on mask.  The relay is on if the mask bit is 1, and off
      * if the bit is 0.  A mask of 0x12 turns on the second and fifth
      * relay. The mask must be between 0x00 (0) and 0x7F (127).  This returns
      * the board number on success, or a negative number when there is an
      * error. */
     int piplate_relay_mask(int address, int mask);

     /** Get the relay state as a bit mask, or -1 if there is an error.  If
      * the bit is 1, the relay is on, and if it is zero, the relay is off.  A
      * state of 0x12 means the second and fifth relays are on. */
     int piplate_relay_state(int address);


     /** Turn a relay LED on.  The address is from 0 to 7, and the LED number
      * is 1 to 7.  This returns the board number on success, or a negative
      * number when there is an error. */
     int piplate_relay_led_on(int address, int led);
     
     /** Turn a relay LED off.  The address is from 0 to 7, and the LED number
      * is 1 to 7.  This returns the board number on success, or a negative
      * number when there is an error. */
     int piplate_relay_led_off(int address, int led);

     /** Toggle the state of a rely LED.  The address is from 0 to 7, and the
      * LED number is 1 to 7.  This returns the board number on success, or a
      * negative number when there is an error. */
     int piplate_relay_led_toggle(int address, int led);

#ifdef __cplusplus
}
#endif

#endif
