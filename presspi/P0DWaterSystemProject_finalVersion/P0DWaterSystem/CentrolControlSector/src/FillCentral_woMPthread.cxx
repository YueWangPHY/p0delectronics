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
#include "CentralReceiver.h"
#include "CentralAction.h"
#include "MeasureAllDepth.h"

#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"

void CallCentralOperation(std::shared_ptr<CentralAction> pAction, std::shared_ptr<asio::io_service> io_service)
{
    pAction->CentralOperation(io_service);
    io_service->run();
}



int main(int argc, char* argv[])
{
    std::cout<<"Inside Central"<<std::endl;

	int fillupto = 200;//mm in default
	if(argc>1)
		sscanf(argv[1], "%d", &fillupto);
	
    // assgin the port for sending and receiveing, respectively
    short pr = static_cast<short>(PortNum::PPtoC) ;
    short ps = static_cast<short>(PortNum::CtoPP) ;

	std::string filepath="";
	if(!GetPSReadingfile(filepath))
	{
		std::cout<<filepath<<std::endl;
		std::cout<<"Can't file depth file"<<std::endl;
		return -1;
	}	
    std::shared_ptr<CentralAction> pAction(new CentralAction(ps, pr, 1, filepath, fillupto));//to fill set 1
//    std::shared_ptr<CentralAction> pAction(new CentralAction(ps, pr, 0, filepath, fillupto));//to do nthing set 0


    std::shared_ptr<asio::io_service> io_service_operation(new asio::io_service);
    std::vector<std::thread> Threads;

    Threads.emplace_back(std::thread(&CentralAction::CentralReceiveAction, pAction));
	Threads.emplace_back(std::thread(CallCentralOperation, pAction, io_service_operation));

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }


    std::cout<<"finish..."<<std::endl;
	return 0;
}
