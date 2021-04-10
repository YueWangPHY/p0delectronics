#ifndef PSACTION_H
#define PSACTION_H

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
#include "ReadPressureSensors.h"
#include "InterpretBag_PS.h"
#include "PSReceiver.h"
#include "PSSender.h"
#include "PSSectorBase.h"

class PSAction
{
public:
	PSAction(int NM=20){
		flag_alldone=false;
		fortest = 100;
		NMeasures = NM;
		for(int i=0;i<NMAXBAGS;i++)
			BBCmap[i]={-1,-1,-1};
	}
	PSAction(short portS, short portR, int NM=20){
		flag_alldone=false;
		portSend = portS;
		portReceive = portR;
		fortest = 200;
		NMeasures = NM;
        for(int i=0;i<NMAXBAGS;i++)
            BBCmap[i]={-1,-1,-1};
	asio::io_service::work worksend(io_service_send);

	}
	std::pair<short, short> GetPortsUsed()
	{
		std::pair<short, short> ports;
		ports.first = portSend;
		ports.second = portReceive;
		return ports;
	}
	int PSReceiveAction();//(asio::io_service& io_service, const int port);
	int PSSendAction(std::string message);//(asio::io_service& io_service, const int port, std::string message);
	int InitBagBoardChannelMap(std::string map);
	void PSOperation(std::shared_ptr<asio::io_service> io_service); 
public:
	bool flag_alldone=false;
	int fortest = -1;
	struct_BagBoardChannel BBCmap[NMAXBAGS];//when filled, will be sort in order of bag id, i.e. bag from 1 to 50.
private:
	short portSend = -1;
	short portReceive = -1;
	asio::io_service io_service_net;
	asio::io_service io_service_send;
	int NMeasures;// set 20 by default	
};

int PSAction::PSReceiveAction()//(asio::io_service& io_service, const int port)
{
    const short portNo = portReceive;
    try{
        PSReceiver receive(io_service_net, portNo);
        io_service_net.run();

    }
    catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int PSAction::PSSendAction(std::string message)//(asio::io_service& io_service, const int port, std::string message)
{
    const short portNo = portSend;
    try{
        PSSender send(io_service_send, portNo, message);
        io_service_send.run();
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}


int PSAction::InitBagBoardChannelMap(std::string map)
{
	int tmpBags[NMAXBAGS], tmpBoards[NMAXBAGS], tmpChannels[NMAXBAGS];
	if(InterpretBag3D_PS(map, BBCmap)<0)
	{
		std::cout<<"Cannot InitBagBoardChannelMap"<<std::endl;
		return -1;
	}
	//sort the arrays in order of bag id 	
	std::sort(BBCmap, BBCmap+NMAXBAGS, sortstructBBC);
	return 0;
}


void PSAction::PSOperation(std::shared_ptr<asio::io_service> io_service)
{

    if(flag_alldone)
        return;
    std::cout<<"In PSOperation"<<std::endl;
    std::shared_ptr<std::string> ptr_flagMsg(new std::string("Nothing0"));
	{
		std::unique_lock<std::mutex> lock(lock_PSReceivdMsgQ);
		if(flag_alldone)
			return;
		cond_PS.wait(lock, []{return !ptr_PSReceivdMsgQ.empty();});
		ptr_flagMsg = ptr_PSReceivdMsgQ.front();
		ptr_PSReceivdMsgQ.pop();
		lock.unlock();
	}

    if(*ptr_flagMsg=="AllDone50")
    {
        flag_alldone=true;
        std::cout<<"flag_alldone=true"<<std::endl;
    }

    std::cout<<"The received msg is "<<*ptr_flagMsg<<std::endl;

	std::pair<int, int> ReceivedCMD = InterpretCMD(*ptr_flagMsg);
	double measuredDepth = -999;
	if(ReceivedCMD.first==0)//cmd for measure pressure
	{
		int flag = -1;
        for(int i=0;i<NMAXBAGS;i++)//loop and compare below in case there are such mistake: FillBag10.1 // probably the format of 10.1 can be used to show bag10 for 1sec
        {
            if(ReceivedCMD.second == i+1)
            {
                flag= i;
                break;
            }
        }
		if(flag != -1)
		{
			//because already sort in InitBogBoardChannel in order of Bag id. SO here just go the index. 
			int iboard = BBCmap[flag].board;//consider the bag id in map starts from 1 and in array starts from 0	
			int ichannel = BBCmap[flag].channel;
			
			measuredDepth =	MeasureDepth(iboard, ichannel, NMeasures);
			std::string tosend ="Bag" + std::to_string(flag+1)+ COMMANDSTRING[COMMAND4CCSTART]+std::to_string(measuredDepth);//todo: COMMANDSTRING[4] should make it more user friendly. measuredDepth should constrain its digits
			PSSendAction(tosend);	
			std::cout<<"TOsend = "<<tosend<<std::endl;
		}
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(5));	

    if(!flag_alldone)
		io_service->post(std::bind(&PSAction::PSOperation, this, io_service));
    else
        return;
}




#endif
