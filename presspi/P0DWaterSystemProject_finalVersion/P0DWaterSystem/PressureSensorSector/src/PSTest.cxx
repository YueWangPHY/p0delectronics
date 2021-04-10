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
//#include "Basic.h"
#include "GlobalBase.h"
#include "PSReceiver.h"
#include "PSAction.h"
//#include "PSAction.hxx"
#include "InterpretBag_PS.h"


void CallPSOperation(std::shared_ptr<PSAction> psAction, std::shared_ptr<asio::io_service> io_service)
{
	psAction->PSOperation(io_service);
	io_service->run();
	
}

int main()//(std::queue<std::string> *ReceivedMessages)
{
    std::cout<<"Inside Receive"<<std::endl;
	std::string str;
	if(GetPSBagBoardChannelMap(str))
		std::cout<<str<<std::endl;
	int ibag = 10;
	std::pair<int, int> boardchannel = FindPSBoardChannelofBag(str, ibag);
	std::cout<<"bag "<<ibag<<" is at "<<boardchannel.first<<" "<<boardchannel.second<<std::endl;

	// assgin the port for sending and receiveing, respectively
	short ps = static_cast<short>(PortNum::PStoC) ;
	short pr = static_cast<short>(PortNum::CtoPS) ;

	std::shared_ptr<PSAction> psAction(new PSAction(ps, pr));
	psAction->InitBagBoardChannelMap(str);
	
	std::pair<short, short> ports =	psAction->GetPortsUsed();
	std::cout<<"port1: "<<ports.first<<std::endl;
	std::cout<<"port2: "<<ports.second<<std::endl;

	std::shared_ptr<asio::io_service> io_service_operation(new asio::io_service);
	std::vector<std::thread> Threads;

	Threads.emplace_back(std::thread(&PSAction::PSReceiveAction, psAction));
//	Threads.emplace_back(std::thread(&PSAction::PSOperation, psAction, io_service_operation));
	Threads.emplace_back(std::thread(CallPSOperation, psAction, io_service_operation));

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }

//	io_service_operation->run();
	
	std::cout<<"finish..."<<std::endl;
	return 0;
}





