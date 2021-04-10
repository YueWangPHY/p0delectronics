#ifndef CENTRALACTION_H
#define CENTRALACTION_H

#define ASIO_STANDALONE
#include <asio.hpp>

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "GlobalBase.h"
#include "InterpretCMD.h"
#include "InterpretBag_PS.h"
#include "ReadPressureSensors.h"
#include "CentralBase.h"
#include "CentralSender.h"
#include "CentralReceiver.h"
#include "PiPlateSectorBase.h"


class CentralAction{

public:
	CentralAction(short portS, short portR, int op, std::string name, int depthcutval):DEPTHCUT(depthcutval){//in op here means which operation among fill, purge and drain you want to perform. todo: enum
        portSend = portS;
        portReceive = portR;
		OperationTodo = op;
		depthfileName = name;
		OperationDone = false;
		countMultifill = 0;
		countMultidrain = 0;
		prevlowestbag = -2;
		prevhighestbag = -2;	
		filecontent.clear();
	}

	void StopWaiting(const asio::error_code& error);
	void WaitingTimer(std::shared_ptr<asio::steady_timer> p_timer, std::shared_ptr<asio::io_service> p_io);//p_io is different fromptr_io for CentralOperation
	void CentralReceiveAction();
	void CentralSendAction(std::string message);
	std::string ReadDepthfile();//(std::string fileName);//fill vector filecontent and return the timer we start to read the file
	void CentralOperation(std::shared_ptr<asio::io_service> ptr_io);
	void FillOperation();
	void DrainOperation();
	void DrainOneBagEachTimeOperation();
	void DrainMultiBagsEachTimeOperation();
	void MonitorOperation();
	
//	void CentralDepthMeaureAction();

private:
    short portSend = -1;
    short portReceive = -1;
	int OperationTodo = -1; //OperationTodo here means which operation among fill, purge and drain you want to perform. todo: enum: 1 fill, 2 purge, 3 drain
	std::string depthfileName = "";
	std::vector<std::string>  filecontent;
	bool OperationDone;

	int prevlowestbag;// = -2;//not -1 just to be diff from the default vlue of lowest bags id. although in principle it shoudn't affect anything
	int prevhighestbag;// = -2;//not -1 just to be diff from the default vlue of highest bags id. although in principle it shoudn't affect anything
	int countMultifill;// = 0;
	int countMultidrain;// = 0;	

	const int WaitingTime = RELAYOPENTIMELENGTH+10;//in sec //this is the time that WaitingTimer wait for the feedback after sending cmd. This should be longer than the time for relays opening

	const int DEPTHCUT;//MAX for fill and Min for drain
};

void CentralAction::StopWaiting(const asio::error_code& error)
{
    if(!error)
    {
        std::cout<<"******Handler StopWaiting is called******"<<std::endl;
        {
            std::lock_guard<std::mutex> lock(send_rec);
            toreset = true;
        }
        cond_CC.notify_all();
    }

}


void CentralAction::WaitingTimer(std::shared_ptr<asio::steady_timer> p_timer, std::shared_ptr<asio::io_service> p_io)
//void CentralAction::WaitingTimer(std::shared_ptr<asio::io_service> p_io)
{
//	std::cout<<"WaitingTime is "<<WaitingTime<<std::endl;
	p_timer->expires_from_now(std::chrono::seconds(RELAYOPENTIMELENGTH+10)); 
//	p_timer->expires_from_now(std::chrono::seconds(WaitingTime)); 
	p_timer->async_wait(std::bind(&CentralAction::StopWaiting, this, std::placeholders::_1));

	p_io->run();
}

void CentralAction::CentralReceiveAction()
{
    const short portNo = portReceive;
    try{
        asio::io_service io;
        CentralReceiver receive(io, portNo);
        io.run();
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return ;
}

void CentralAction::CentralSendAction(std::string message)
{
    const short portNo = portSend;
    try{
        asio::io_service io;
        CentralSender send(io, portNo, message);
        io.run();
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return ;
}

std::string CentralAction::ReadDepthfile()//(std::string fileName)
{
//	std::string fileName = depthfileName;
//    std::cout<<fileName<<std::endl;
    std::string eachline = "";
	std::string currentTime = "";
    filecontent.clear();
    std::string fileopen = depthfileName;

	int depthfilefd;	
	struct flock depthfilelk;
//	depthfilefd = open("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt", O_RDWR);	
	depthfilefd = open(depthfileName.c_str(), O_RDWR);
//	depthfilefd = open("/home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/macro/depth_fillcentral.txt", O_RDWR);
	
	if(depthfilefd<0)
	{
		std::cout<<"In CentralAction: depthfilefd<0"<<std::endl;
	}

	std::cout<<"going to ask lock"<<std::endl;
	depthfilelk.l_type = F_WRLCK;
    depthfilelk.l_whence = SEEK_SET;
    depthfilelk.l_start = 0;
    depthfilelk.l_len = 0;
	fcntl(depthfilefd, F_SETLKW, &depthfilelk);
	std::cout<<"inlock"<<std::endl;

	currentTime = GetCurrentTime();

	std::ifstream inputfile(fileopen.c_str());
	if(inputfile.is_open())
	{
		while(getline(inputfile, eachline))
			filecontent.push_back(eachline);
	}
	else
		std::cout<<"CANNOT OPEN THE FILE"<<std::endl;

	inputfile.close();

	depthfilelk.l_type = F_UNLCK;
	fcntl(depthfilefd, F_SETLKW, &depthfilelk);
	close(depthfilefd);
	std::cout<<"Out of lock"<<std::endl;
	return currentTime;
}

void CentralAction::CentralOperation(std::shared_ptr<asio::io_service> ptr_io)
{
	std::string currentTime = ReadDepthfile();
	int size = filecontent.size();
	if(size != NMAXBAGS+1)
	{
		std::cout<<"size ="<< size<<std::endl;
		std::cout<<"Depth file structure seems wrong. Please check!!!"<<std::endl;
	}
	else{
	//todo: how long does the ps part take to measure depth in all 50 bag in one turn: if NMeasurement=20, then it's about 2-3s/turn //another thought: put the time stamp of last measurement in the file too, so that we can check the period of the measurement and make a more precise estimation of how recent when the measurement was done
		std::cout<<"OperationTodo="<<OperationTodo<<std::endl;
		int validtime = 6;//sec
		if(OperationTodo==0)//monitor operation
			validtime = 20;// increase time

		if(GetTimeDifference(filecontent[0], currentTime)<0||GetTimeDifference(filecontent[0], currentTime)>validtime)
		{
			std::shared_ptr<asio::steady_timer> ptr_t(new asio::steady_timer(*ptr_io));
			ptr_t->expires_from_now(std::chrono::seconds(5));//time to wait need to be changed after testing.
			ptr_t->wait();
			std::cout<<"Re Read"<<std::endl;
		}
		else{
			if(OperationTodo==0)//to monitor
				MonitorOperation();
			else if(OperationTodo==1)//to fill
				FillOperation();
			else if(OperationTodo==2)// to purge gas
				std::cout<<"purge gas"<<std::endl;//no purge gas operation so far
			else if(OperationTodo==3)//to drain water
				DrainOperation();
			else
				std::cout<<"No operation is going to be peformed"<<std::endl;
		}


	}

	if(!OperationDone)	
		ptr_io->post(std::bind(&CentralAction::CentralOperation, this, ptr_io));	
	else 
		return;
}

void CentralAction::FillOperation()
{
	int size = filecontent.size();
	int bagId = -1;
	int depth = -1;//in unit of mm
	int minbag = -1, mindepth = DEPTHCUT, maxbag = -1, maxdepth = 0;
	for(int i=1; i<size; i++)//first line i.e. line0 is time and has been checked above
	{
		sscanf(filecontent[i].c_str(),"%d%*c%d",&bagId, &depth);
		if(depth<mindepth)
		{
			mindepth = depth;
			minbag = bagId;
		}
		if(depth>maxdepth)
		{
			maxdepth = depth;
			maxbag = bagId;
		}
//two lines belows are commented fo now when we use pesudo pressure files. When we use real measured files, they should be uncomment.
		if((maxdepth-mindepth>MAXDEPTHDIFF)&&(mindepth>0))//no larger than NMAXDEPTHDIFF 
			CentralSendAction(CreateCMD(COMMAND4PPSTART+6, 50));// in case some relays are not closed. ask them to close
	}
	if(minbag==-1&&mindepth==DEPTHCUT)//all bags are above DEPTHCUT;
	{
		CentralSendAction("AllDone50");
		{
			std::lock_guard<std::mutex> lock1(send_rec);
			f_sent = true;
			toleave = true;
			OperationDone = true;
		}
		cond_CC.notify_all();
		return;
	}
	if(minbag == prevlowestbag)
		countMultifill++;
	else 
		countMultifill = 0;
	
	if(countMultifill>2)
	{
		CentralSendAction("AllDone50");
        {
            std::lock_guard<std::mutex> lock1(send_rec);
            f_sent = true;
            toleave = true;
            OperationDone = true;
        }
        cond_CC.notify_all();
		std::cout<<"Bag "<<minbag<<" has been continuously asked to fill for more than 3 times. To avoid overfilling, the entire filling procedure is stopped."
			<<" Please check the valve or the depth measurement"<<std::endl; 
        return;
	}		
	
	
	CentralSendAction(CreateCMD(COMMAND4PPSTART, minbag));
	{
		std::lock_guard<std::mutex> lock1(send_rec);
		f_sent = true;
	}
	cond_CC.notify_all();
	std::cout<<"notify receiver"<<std::endl;

////////////////////
	std::unique_lock<std::mutex> lock2(send_rec);
	std::cout<<"StartTimer"<<std::endl;

//	std::shared_ptr<asio::io_service> p_io(new asio::io_service);
//	std::shared_ptr<asio::steady_timer> ptr_timer(new asio::steady_timer(*p_io));
//	std::thread thread1(TimerThread, ptr_timer, p_io);
//          io.run();//if io run is in the same thread with cond or sleep, the results from other thread using this io won't affect this thread until the cond wait or sleep is dpwn.

//	std::thread thread1(std::bind(&CentralAction::InternalTimer, this));

	std::shared_ptr<asio::io_service> p_io(new asio::io_service);

	std::shared_ptr<asio::steady_timer> p_timer(new asio::steady_timer(*p_io));
	std::thread thread1(std::bind(&CentralAction::WaitingTimer, this, p_timer,p_io));

//	std::thread thread1(std::bind(&CentralAction::WaitingTimer, this, p_io));

	cond_CC.wait(lock2, []{return f_received||toreset;});

//	ptr_timer->cancel();
//	p_internaltimer->cancel();
	p_timer->cancel();
	std::cout<<"CancelTimer"<<std::endl;

	f_sent = false;
	f_received = false;

	if(toreset==true)
	{
		toreset = false;
		CentralSendAction(CreateCMD(COMMAND4PPSTART+6, 50));
	}

	thread1.join();//code after join will be excuted after the thread has been done. so put the join in the end of the scope
	lock2.unlock();
	
	prevlowestbag = minbag;
////////////////////
}


void CentralAction::DrainOperation()// send NMAXBAGSDRAINSIM commands as a set and wait for the feedback of this set and then go to another set of commmands
{
	std::cout<<"In Drain"<<std::endl;
	if(NMAXBAGSDRAINSIM==1)
		DrainOneBagEachTimeOperation();
	else
		DrainMultiBagsEachTimeOperation();
//		std::cout<<"To devolope algo to drain multiple bags at the same time"<<std::endl;
/*
    int size = filecontent.size();
    int bagId = -1;
    int depth = -1;//in unit of mm

	int maxbags[NMAXBAGSDRAINSIM], maxdepths[NMAXBAGSDRAINSIM];
	for(int j=0;j<NMAXBAGSDRAINSIM;j++)
	{
		maxbags[j] = -1;
		maxdepths[j] = DEPTHCUT; 
	}
	for(int i=1; i<size; i++)//first line i.e. line0 is time and has been checked above
    {
        sscanf(filecontent[i].c_str(),"%d%*c%d",&bagId, &depth);
        if(depth>maxdepths[0])
        {
            maxdepths[0] = depth;
			maxbags[0] = bagId;
			for(int ibag=0;ibag<NMAXBAGSDRAINSIM-1; ibag++)// why don't I just sort and get the first 4???????
			{
				if(maxdepths[ibag]>maxdepths[ibag+1])		
				{
					int tmpdep = maxdepths[ibag+1];
					int tmpbag = maxbags[ibag+1];
					maxdepths[ibag+1] = maxdepths[ibag];
					maxbags[ibag+1] = maxbags[ibag];
					maxdepths[ibag] = tmpdep;
					maxbags[ibag] = tmpbag;
				}
			}
        }
    }

    if(maxbags[NMAXBAGSDRAINSIM-1]==-1&&maxdepths[NMAXBAGSDRAINSIM-1]==DEPTHCUT)//all bags are above DEPTHCUT;
    {
        CentralSendAction("AllDone50");
        {
            std::lock_guard<std::mutex> lock1(send_rec);
            f_sent = true;
            toleave = true;
            OperationDone = true;
        }
        cond_CC.notify_all();
        return;
    }
	for(int i=0; i<NMAXBAGSDRAINSIM;i++)
		CentralSendAction(CreateCMD(COMMAND4PPSTART+2, maxbags[i]));

    {
        std::lock_guard<std::mutex> lock1(send_rec);
        f_sent = true;
    }
    cond_CC.notify_all();
    std::cout<<"notify receiver"<<std::endl;

////////////////////same with that in FillOperation 
    std::unique_lock<std::mutex> lock2(send_rec);
    std::cout<<"StartTimer"<<std::endl;

    std::shared_ptr<asio::io_service> p_io(new asio::io_service);
    std::shared_ptr<asio::steady_timer> p_timer(new asio::steady_timer(*p_io));
    std::thread thread1(std::bind(&CentralAction::WaitingTimer, this, p_timer, p_io));


    cond_CC.wait(lock2, []{return f_received||toreset;});

    std::cout<<"CancelTimer"<<std::endl;
    p_timer->cancel();

    f_sent = false;
    f_received = false;

    if(toreset==true)
    {
        toreset = false;
        CentralSendAction(CreateCMD(COMMAND4PPSTART+6, 50));
    }

    thread1.join();//code after join will be excuted after the thread has been done. so put the join in the end of the scope
    lock2.unlock();
*/
////////////////////

//	return;
}

void CentralAction::DrainMultiBagsEachTimeOperation()
{
	std::cout<<"To devolope algo to drain multiple bags at the same time"<<std::endl;
}


void CentralAction::DrainOneBagEachTimeOperation()
{
	int size = filecontent.size();
	int bagId = -1;
	int depth = -1;//in unit of mm
//	int minbag = -1, mindepth = DEPTHCUT, 
	int maxbag = -1, maxdepth = DEPTHCUT;
	for(int i=1; i<size; i++)//first line i.e. line0 is time and has been checked above
	{
		sscanf(filecontent[i].c_str(),"%d%*c%d",&bagId, &depth);
		if(depth>maxdepth)
		{
			maxdepth = depth;
			maxbag = bagId;
		}
//		if(depth>maxdepth)
//		{
//			maxdepth = depth;
//			maxbag = bagId;
//		}
//two lines belows are commented fo now when we use pesudo pressure files. When we use real measured files, they should be uncomment.
//		if((maxdepth-mindepth>MAXDEPTHDIFF)&&(mindepth>0))//no larger than NMAXDEPTHDIFF 
//			CentralSendAction(CreateCMD(COMMAND4PPSTART+6, 50));// in case some relays are not closed. ask them to close
	}
	if(maxbag==-1&&maxdepth==DEPTHCUT)//all bags are lower than DEPTHCUT;
	{
		CentralSendAction("AllDone50");
		{
			std::lock_guard<std::mutex> lock1(send_rec);
			f_sent = true;
			toleave = true;
			OperationDone = true;
		}
		cond_CC.notify_all();
		return;
	}
	if(maxbag == prevhighestbag)
		countMultidrain++;
	else 
		countMultidrain = 0;
	
	if(countMultidrain>2)
	{
		CentralSendAction("AllDone50");
        {
            std::lock_guard<std::mutex> lock1(send_rec);
            f_sent = true;
            toleave = true;
            OperationDone = true;
        }
        cond_CC.notify_all();
		std::cout<<"Bag "<<maxbag<<" has been continuously asked to drain for more than 3 times."
			<<" Please check the valve or the depth measurement"<<std::endl; 
        return;
	}		
	
	
	CentralSendAction(CreateCMD(COMMAND4PPSTART+2, maxbag));
	{
		std::lock_guard<std::mutex> lock1(send_rec);
		f_sent = true;
	}
	cond_CC.notify_all();
	std::cout<<"notify receiver"<<std::endl;

////////////////////
	std::unique_lock<std::mutex> lock2(send_rec);
	std::cout<<"StartTimer"<<std::endl;

//	std::shared_ptr<asio::io_service> p_io(new asio::io_service);
//	std::shared_ptr<asio::steady_timer> ptr_timer(new asio::steady_timer(*p_io));
//	std::thread thread1(TimerThread, ptr_timer, p_io);
//          io.run();//if io run is in the same thread with cond or sleep, the results from other thread using this io won't affect this thread until the cond wait or sleep is dpwn.

//	std::thread thread1(std::bind(&CentralAction::InternalTimer, this));

	std::shared_ptr<asio::io_service> p_io(new asio::io_service);

	std::shared_ptr<asio::steady_timer> p_timer(new asio::steady_timer(*p_io));
	std::thread thread1(std::bind(&CentralAction::WaitingTimer, this, p_timer,p_io));

//	std::thread thread1(std::bind(&CentralAction::WaitingTimer, this, p_io));

	cond_CC.wait(lock2, []{return f_received||toreset;});

//	ptr_timer->cancel();
//	p_internaltimer->cancel();
	p_timer->cancel();
	std::cout<<"CancelTimer"<<std::endl;

	f_sent = false;
	f_received = false;

	if(toreset==true)
	{
		toreset = false;
		CentralSendAction(CreateCMD(COMMAND4PPSTART+6, 50));
	}

	thread1.join();//code after join will be excuted after the thread has been done. so put the join in the end of the scope
	lock2.unlock();
	
	prevhighestbag = maxbag;
////////////////////
}


//void CentralAction::CentralDepthMeaureAction()

void CentralAction::MonitorOperation()
{
	int size = filecontent.size();
	int bagId = -1;
	int depth = -1;//in unit of mm
	int minbag = -1, mindepth = DEPTHCUT, maxbag = -1, maxdepth = 0;
	bool allabove = true;
	for(int i=1; i<size; i++)//first line i.e. line0 is time and has been checked above
	{
		sscanf(filecontent[i].c_str(),"%d%*c%d",&bagId, &depth);
		if(DEPTHCUT-depth>30)//30mm
		{
			allabove = false;
			std::cout<<"it seems that bag "<<bagId<<" depth decreased"<<std::endl;
			std::cout<<"the program will top off automatically"<<std::endl; 
			std::cout<<"But P0D expert should find the reason why the depth goes down." 
					<<"Especially need to check ig the bag is leaking"<<std::endl;
			CentralSendAction(CreateCMD(COMMAND4PPSTART, bagId));
		}
	}
	if(!allabove)
	{
		std::cout<<"Monitor program will come back and check the depth after some time"<<std::endl;
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}
	else
	{
		std::cout<<"Every bag is above the depthcut"<<std::endl;
		std::cout<<"will check again in 1 hour"<<std::endl;
		std::this_thread::sleep_for(std::chrono::minutes(60));
	}
	return;
}


#endif



