#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>

#include "piplate.h"
#include "Interface.h" 

int main(int argc, char* argv[]) {
    std::cout << "start init" << std::endl;

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

	for(int i=0;i<255;++i)//PIPLATE_MAX_PLATE_ADDRESS =255
		piplate_relay_mask(i,0);
	piplate_close();


	std::cout<<"done init"<<std::endl;

	return 0;
}
