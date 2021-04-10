#ifndef PIPLATEACTION_H
#define PIPLATEACTION_H

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

class PiPlateAction{//This class is for operations on relay when communicating with contral control program
public:
    PiPlateAction(){
        flag_alldone=false;
		BBCmap.clear();
		FillMap.clear();
		PGMap.clear();
		DrainMap.clear();	
		if(InitPiPlate()<0)
			std::cout<<"Fail to init PiPlates!"<<std::endl;
    }

    PiPlateAction(short portS, short portR){
        flag_alldone=false;
        portSend = portS;
        portReceive = portR;
		BBCmap.clear();
        FillMap.clear();
        PGMap.clear();
        DrainMap.clear();
        if(InitPiPlate()<0)
            std::cout<<"Fail to init PiPlates!"<<std::endl;
 
	}

    std::pair<short, short> GetPortsUsed(){
        std::pair<short, short> ports;
        ports.first = portSend;
        ports.second = portReceive;
        return ports;
    }

	int InitPiPlate();
	bool CheckRelayState(int addr, int relay);
    int PiPlateReceiveAction();//(asio::io_service& io_service, const int port);
    int PiPlateSendAction(std::string message);//(asio::io_service& io_service, const int port, std::string message);
	int InitBagBoardChannelMap(std::string map);
	struct_BagBoardChannel GetBagBoardChannel(int bagId, std::vector<struct_BagBoardChannel> map);
    void PiPlateOperation(std::shared_ptr<asio::io_service> io_service);
	void OperationUnderCommand(std::string cmd);//(int cmdId, int bagId);
	void RelayOperation(bool OC, struct_BagBoardChannel bbc);//(int cmdId, int bagId);
public:
    bool flag_alldone=false;
	std::vector<std::pair<int, struct_BagBoardChannel>> BBCmap;//max size should be NMAXRELAYS
	std::vector<struct_BagBoardChannel> FillMap;
	std::vector<struct_BagBoardChannel> PGMap;
	std::vector<struct_BagBoardChannel> DrainMap;
private:
    short portSend = -1;
    short portReceive = -1;
    asio::io_service io_service_rec;

};


int PiPlateAction::InitPiPlate()
{
#ifdef WITH_INTERRUPT
        if (piplate_init_interrupt(1)<0) {
            std::cout << "Error opening piplate with interrupt(1)\n" << std::endl;
            return -1;
        }
#else
        if (piplate_init()<0) {
            std::cout << "Error opening piplate with piplate_init()<0\n" << std::endl;
            return -1;
        }
#endif
        return 0;

}

bool PiPlateAction::CheckRelayState(int addr, int relay)
{
    int piplate_state = piplate_relay_state(addr) ;
    if(piplate_state<0)
        return 0;
    int bit_id = relay-1;
    int relay_state = (piplate_state>>bit_id)&1;
    if(relay_state==1)
        return 1;
    else
        return 0;

}

int PiPlateAction::PiPlateReceiveAction()
{
    const short portNo = portReceive;
    try{
        PiPlateReceiver receive(io_service_rec, portNo);
        io_service_rec.run();
    }
    catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;

}


int PiPlateAction::PiPlateSendAction(std::string message)//(asio::io_service& io_service, const int port, std::string message)
{
    const short portNo = portSend;
    try{
		asio::io_service io_service_send;
        PiPlateSender send(io_service_send, portNo, message);
        io_service_send.run();
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int PiPlateAction::InitBagBoardChannelMap(std::string map)
{
    if(InterpretBagwFunc_PiPlate(map, FillMap, PGMap, DrainMap)<0)
    {
        std::cout<<"Cannot InitBagBoardChannelMap"<<std::endl;
        return -1;
    }

    //sort the arrays in order of bag id
    int NFBags = FillMap.size();
    int NPBags = PGMap.size();
    int NDBags = DrainMap.size();

    std::sort(FillMap.begin(), FillMap.end(), sortstructBBC);
    std::sort(PGMap.begin(), PGMap.end(), sortstructBBC);
    std::sort(DrainMap.begin(), DrainMap.end(), sortstructBBC);
    return 0;
}

struct_BagBoardChannel PiPlateAction::GetBagBoardChannel(int bagId, std::vector<struct_BagBoardChannel> map)
{
    int size = map.size();
    struct_BagBoardChannel tmp={-1,-1,-1};
    if(bagId>=map[0].bag&&bagId<=map[size-1].bag)
    {
        for(int i=0;i<size;i++)
        {
            if(bagId==map[i].bag)
                return map[i];
        }
    }
    return tmp;
}

void PiPlateAction::RelayOperation(bool OC, struct_BagBoardChannel bbc)//OpenorClose: 1-open, 0-clase
{
    int addr = bbc.board;
    int relay = bbc.channel;
    if(OC)
    {
        {
            std::lock_guard<std::mutex> lock(lock_PPOperation);
            if(CheckRelayState(addr, relay))
            {
                std::cout<<"Relay "<<addr<<" "<<relay<<" already Open"<<std::endl;
				std::cout<<"******will close this relay soon!!! But just be careful about the depth in this bag!!!!!******"<<std::endl;
//                return;
            }
			else{
				std::cout << "turn on relay"<<addr<<","<<relay << std::endl;
				piplate_relay_on(addr,relay);
			}
        }
        std::this_thread::sleep_for(std::chrono::seconds(RELAYOPENTIMELENGTH));
        {
            std::lock_guard<std::mutex> lock(lock_PPOperation);
            piplate_relay_off(addr,relay);
        }
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(lock_PPOperation);
            piplate_relay_off(addr,relay);
        }
    }
//      sleep(2);

}

void PiPlateAction::OperationUnderCommand(std::string cmd)
{
    std::pair<int, int> ReceivedCMD = InterpretCMD(cmd);
    int cmdId = ReceivedCMD.first;
    int bagId = ReceivedCMD.second;
//	std::cout<<"cmdId: "<<cmdId<<" bagId: "<<bagId<<std::endl;

    struct_BagBoardChannel BoardChannelTodo = {-1,1,1};
    switch(cmdId)
    {
        case COMMAND4PPSTART: //fill
            BoardChannelTodo = GetBagBoardChannel(bagId, FillMap);
			if(BoardChannelTodo.bag==-1)
                break;
            RelayOperation(1, BoardChannelTodo);
			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId )); 
            break;
        case COMMAND4PPSTART+1: //purge
            BoardChannelTodo = GetBagBoardChannel(bagId, PGMap);
			if(BoardChannelTodo.bag==-1)
                break;
            RelayOperation(1, BoardChannelTodo);
			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId )); 
            break;
        case COMMAND4PPSTART+2: //drain
            BoardChannelTodo = GetBagBoardChannel(bagId, DrainMap);
			if(BoardChannelTodo.bag==-1)
                break;
            RelayOperation(1, BoardChannelTodo);
			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId )); 
            break;
        case COMMAND4PPSTART+3:
            BoardChannelTodo = GetBagBoardChannel(bagId, FillMap);
            RelayOperation(0, BoardChannelTodo);
//			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId ));
            break;
        case COMMAND4PPSTART+4:
            BoardChannelTodo = GetBagBoardChannel(bagId, PGMap);
            RelayOperation(0, BoardChannelTodo);
//			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId ));
            break;
        case COMMAND4PPSTART+5:
            BoardChannelTodo = GetBagBoardChannel(bagId, DrainMap);
            RelayOperation(0, BoardChannelTodo);
//			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId )); 
            break;
		case COMMAND4PPSTART+6: //close all relays and piplates in case some unexpected things happen and init piplate again to make then ready to work
			for(int i=0;i<255;++i)//PIPLATE_MAX_PLATE_ADDRESS =255
				piplate_relay_mask(i,0);
			piplate_close();
			InitPiPlate();
			std::cout<<"All Relays are closed"<<std::endl;
//			PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId ));
            break;

        default:
            break;

    }

}

void PiPlateAction::PiPlateOperation(std::shared_ptr<asio::io_service> io_service)
{
	if(flag_alldone)
	{
		PiPlateSendAction("AllDone50");
        return;
	}
    std::cout<<"In ReadOne"<<std::endl;
    std::shared_ptr<std::string> ptr_flagMsg(new std::string("Nothing0"));
    std::unique_lock<std::mutex> lock(lock_PPReceivdMsgQ);
    if(flag_alldone)
	{
		PiPlateSendAction("AllDone50");
        return;
	}
//    {
//        std::lock_guard<std::mutex> lockC(lock_InCondWaitCounter);
//        InCondWaitCounter++;
//    }
    cond_PP.wait(lock, []{return !ptr_PPReceivdMsgQ.empty();});
    if(flag_alldone)
	{
		PiPlateSendAction("AllDone50");
        return;
	}
//    {
//        std::lock_guard<std::mutex> lockC(lock_InCondWaitCounter);
//        InCondWaitCounter--;
//    }
    ptr_flagMsg = ptr_PPReceivdMsgQ.front();
    ptr_PPReceivdMsgQ.pop();
	std::cout<<"size="<<ptr_PPReceivdMsgQ.size()<<std::endl;
    lock.unlock();
    if(*ptr_flagMsg=="AllDone50")
    {
        flag_alldone=true;
        std::cout<<"flag_alldone=true"<<std::endl;
//		PiPlateSendAction("AllDone50");
        return;
    }
    OperationUnderCommand(*ptr_flagMsg);
//	PiPlateSendAction(CreateCMD(COMMAND4CCSTART+1, bagId )); 
    if(!flag_alldone)
        io_service->post(std::bind(&PiPlateAction::PiPlateOperation, this, io_service));
    else
        return;

}



#endif
