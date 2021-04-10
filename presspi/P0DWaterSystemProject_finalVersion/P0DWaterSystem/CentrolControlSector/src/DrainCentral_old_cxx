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

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"

void CallCentralOperation(std::shared_ptr<CentralAction> pAction, std::shared_ptr<asio::io_service> io_service)
{
    pAction->CentralOperation(io_service);
    io_service->run();
}

int main()
{
    std::cout<<"Inside Central"<<std::endl;

    // assgin the port for sending and receiveing, respectively
    short pr = static_cast<short>(PortNum::PPtoC) ;
    short ps = static_cast<short>(PortNum::CtoPP) ;

	std::string filepath = "/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt";
    std::shared_ptr<CentralAction> pAction(new CentralAction(ps, pr, 3, filepath));

    std::shared_ptr<asio::io_service> io_service_operation(new asio::io_service);

//	pAction->CentralOperation(io_service_operation);

    std::vector<std::thread> Threads;

    Threads.emplace_back(std::thread(&CentralAction::CentralReceiveAction, pAction));
    Threads.emplace_back(std::thread(CallCentralOperation, pAction, io_service_operation));
//    Threads.emplace_back(std::thread(CallCentralOperation, pAction, io_service_operation));//to test give to threads of operation.

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }


    std::cout<<"finish..."<<std::endl;
	return 0;
}
