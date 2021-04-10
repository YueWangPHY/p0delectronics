#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <mutex>
#include <thread>

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "GlobalBase.h"
#include "InterpretBag_PS.h"
#include "ReadPressureSensors.h"
#include "CentralBase.h"
#include "CentralSender.h"
//#include "CentralReceiver.h"
#include "BasicReceiver.h"

#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"

int main()
{
    std::cout<<"Inside Central"<<std::endl;

    // assgin the port for sending and receiveing, respectively
    short pr = static_cast<short>(PortNum::PPtoC) ;
    short ps = static_cast<short>(PortNum::CtoPP) ;

	std::ofstream outcmd("RecordBagFillTime.txt");

	for(int i=0; i<50; i++)
	{	
//		if(i+1==23||i+1==32)
//		if(i+1==32)
//			continue;
//		std::string sendmsg =GetCurrentTime+ "FillBag"+
		std::string sendmsg = CreateCMD(COMMAND4PPSTART, i+1);
		outcmd<<sendmsg<<std::endl;
		std::cout<<"going to send"<<std::endl;
		try{
        	asio::io_service io;
        	CentralSender send(io, ps, sendmsg);
        	io.run();
    	}
		catch(std::exception& e){
			std::cerr << "Exception: " << e.what() << "\n";
		}

		std::cout<<"waiting for feedback"<<std::endl;
		try{
			asio::io_service ior;
			BasicReceiver receive(ior, pr);
			ior.run();
		}
		catch(std::exception& e){
			std::cerr << "Exception: " << e.what() << "\n";
		}


	}


    std::cout<<"finish..."<<std::endl;
	return 0;
}
