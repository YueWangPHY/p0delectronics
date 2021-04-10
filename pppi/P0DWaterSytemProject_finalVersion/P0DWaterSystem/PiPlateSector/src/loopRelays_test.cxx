//This program is to loop over the map of relays and bags to see if the map is wrote correctly

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "config.h"
#include "piplate.h"
//#include "Interface.h" 

int main(int argc, char* argv[]) {

#ifdef WITH_INTERRUPT
    if (piplate_init_interrupt(1)<0) {
        std::cout << "Error opening piplate with interrupt(1)\n" << std::endl;
        return 1;
    }
#else
    if (piplate_init()<0) {
        std::cout << "Error opening piplate with piplate_init()<0\n" << std::endl;
        return 1;
    }
#endif

    std::cout << "Hello world" << std::endl;

	int addr=-1, relay=-1;
	int piplateStack = -1, func = -1, bagid = -1; 
	std::string str="";
	if(!GetPPBagBoardChannelMap(str))
	{
		std::cout<<"no map"<<std::endl;
		return 0;
	}
	else 
		std::cout<<str<<std::endl;
	std::ifstream file(str.c_str());
	std::string line;
	if(file.is_open())
	{
		while(getline(file, line))
		{
			sscanf(line.c_str(),"%d%*c%d%*c%d%*c%d%*c%d", &piplateStack, &bagid, &func, &addr, &relay);
			std::cout<<"bag "<<bagid<<std::endl;
			std::cout << "turn on relay "<<addr<<","<<relay << std::endl;
			piplate_relay_on(addr,relay);
			 
			std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;

//			std::this_thread::sleep_for(std::chrono::seconds(RELAYOPENTIMELENGTH));
			sleep(10);//in sec

			std::cout << "turn off relay 0,1" << std::endl;
			piplate_relay_off(addr,relay);

			std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;

			std::cout << "turn off all relays" << std::endl;
			piplate_relay_mask(addr,0);

			std::cout << "relay state: " << piplate_relay_state(addr) << std::endl;
			sleep(5);
		}
	}
    piplate_close();
}
