#define ASIO_STANDALONE

#include <asio.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "config.h"
#include "GlobalBase.h"
#include "InterpretCMD.h"
#include "bcm2835.h"
#include "piplate.h"
#include "Interface.h"
#include "InterpretBag_PiPlate.h"
#include "PiPlateReceiver.h"
#include "PiPlateSender.h"
#include "PiPlateSectorBase.h"
#include "PiPlateAction.h"

void CallPiPlateOperation(std::shared_ptr<PiPlateAction> pAction, std::shared_ptr<asio::io_service> io_service)
{
	pAction->PiPlateOperation(io_service);
	io_service->run();

}

int main()
{
    std::cout<<"Inside Receive"<<std::endl;
    std::string str;
    if(GetPPBagBoardChannelMap(str))
        std::cout<<str<<std::endl;

    // assgin the port for sending and receiveing, respectively
    short ps = static_cast<short>(PortNum::PPtoC) ;
    short pr = static_cast<short>(PortNum::CtoPP) ;

    std::shared_ptr<PiPlateAction> pAction(new PiPlateAction(ps, pr));
    if(pAction->InitBagBoardChannelMap(str)<0)
		return 0;
   
//	std::cout<<"pAction->InitBagBoardChannelMap(str)"<<pAction->InitBagBoardChannelMap(str)<<std::endl;
    std::pair<short, short> ports = pAction->GetPortsUsed();
    std::cout<<"port1: "<<ports.first<<std::endl;
    std::cout<<"port2: "<<ports.second<<std::endl;

    std::shared_ptr<asio::io_service> io_service_operation(new asio::io_service);
    std::vector<std::thread> Threads;

    Threads.emplace_back(std::thread(&PiPlateAction::PiPlateReceiveAction, pAction));
    Threads.emplace_back(std::thread(CallPiPlateOperation, pAction, io_service_operation));
//    Threads.emplace_back(std::thread(CallPiPlateOperation, pAction, io_service_operation));//to test give to threads of operation.

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }


    std::cout<<"finish..."<<std::endl;

	pAction->PiPlateSendAction("AllDone50");

    std::cout<<"close all relays"<<std::endl;
    for(int i=0;i<255;++i)//PIPLATE_MAX_PLATE_ADDRESS =255
        piplate_relay_mask(i,0);
    std::cout<<"close piplates"<<std::endl;
    piplate_close();

    return 0;

}
