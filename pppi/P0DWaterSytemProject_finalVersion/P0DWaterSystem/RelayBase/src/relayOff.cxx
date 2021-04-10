#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>

#include "piplate.h"
#include "Interface.h" 

int main(int argc, char* argv[]) {
    std::cout << "Anybody home?" << std::endl;

#ifdef WITH_INTERRUPT
	std::cout<<"define init_interrupt"<<std::endl;
    if (piplate_init_interrupt(1)<0) {
        std::cout << "Error opening piplate with interrupt(1)\n" << std::endl;
        return 1;
    }
#else
	std::cout<<"NOT define init_interrupt"<<std::endl;
    if (piplate_init()<0) {
        std::cout << "Error opening piplate with piplate_init()<0\n" << std::endl;
        return 1;
    }
#endif


    std::cout << "Hello world" << std::endl;

	int addr=-1, relay=-1;
	std::string parameter = Input();
	std::cout<<parameter<<std::endl;
	sscanf(parameter.c_str(),"%1d%1d",&addr,&relay); 
	Output(addr,relay);

    std::cout << "hardware address and version: "
              << " " << piplate_relay_address(addr)
              << " " << piplate_hardware(piplate_relay_address(addr))
              << std::endl;
    
    std::cout << "firmware address and version: "
              << " " << piplate_relay_address(addr)
              << " " << piplate_firmware(piplate_relay_address(addr))
              << std::endl;
//    std::cout << "turn on relay"<<addr<<","<<relay << std::endl;
//    piplate_relay_on(addr,relay);
     
 //   std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;

/*
    std::cout << "turn on relay 0,6" << std::endl;
    piplate_relay_on(0,6);

    std::cout << "relay state: " << piplate_relay_state(0) << std::endl;
*/
 //   sleep(10);

  //  std::cout << "turn off relay 0,1" << std::endl;
    piplate_relay_off(addr,relay);

    std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;

//    std::cout << "turn off all relays" << std::endl;
  //  piplate_relay_mask(addr,0);

   // std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;

    //piplate_close();
}
