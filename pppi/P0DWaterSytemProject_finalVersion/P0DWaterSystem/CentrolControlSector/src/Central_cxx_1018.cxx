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

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"


//bool toreset = false;
void ResetCounter(const asio::error_code& error)
{
	std::cout<<"Outside of !error"<<std::endl;

	if(!error)
	{
		std::cout<<"ResetCounter is called"<<std::endl;
		{
			std::lock_guard<std::mutex> lock(send_rec);
			toreset = true;	
		}
		cond_CC.notify_one();
	}

}

//void SendMsg(short portSend, std::string message)
void SendMsg(std::string message)
{
    const short portNo = static_cast<short>(PortNum::CtoPP);//portSend;
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

void ReceiveMsg()
{
	const short portNo = static_cast<short>(PortNum::PPtoC);
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

void TimerThread(std::shared_ptr<asio::io_service> ptr_io)
{
            asio::steady_timer t1(*ptr_io, std::chrono::steady_clock::now() + std::chrono::seconds(2));
//          t1.expires_from_now(std::chrono::seconds(2));
            t1.async_wait(&ResetCounter);
	ptr_io->run();
	
}

void ReadDepth(std::shared_ptr<asio::io_service> ptr_io, std::string fileName, int* lowestBag, int* lowestDepth)
{
	std::cout<<fileName<<std::endl;
	std::string eachline = "";
	std::string currentTime = "";
	std::vector<std::string>  filecontent;
	filecontent.clear();
	std::string fileopen = fileName;
	int linecounter = 0;
	int tmpbag = -1, tmpdepth = DEPTHCUT;//which is 1960 for now;//in mm. btw 77in and 78in
	{
		std::lock_guard<std::mutex> lock(lockfile);
		std::cout<<"inlock"<<std::endl;
		currentTime = GetCurrentTime();

		std::ifstream inputfile(fileopen.c_str());	
		if(inputfile.is_open())
		{
			while(getline(inputfile, eachline))//filecontent[linecounter]))
				filecontent.push_back(eachline);
		}
		else 
			std::cout<<"CANNOT OPEN THE FILE"<<std::endl;

		inputfile.close();
	}		


//	std::shared_ptr<asio::steady_timer> ptr_t(new asio::steady_timer(*ptr_io));
///////////////////////////////
	if(GetTimeDifference(filecontent[0], currentTime)<0||GetTimeDifference(filecontent[0], currentTime)>10)//todo: how long does the ps part take to measure depth in all 50 bag in one turn: if NMeasurement=20, then it's about 2-3s/turn //another thought: put the time stamp of last measurement in the file too, so that we can check the period of the measurement and make a more precise estimation of how recent when the measurement was done
	{
		std::shared_ptr<asio::steady_timer> ptr_t(new asio::steady_timer(*ptr_io));
        ptr_t->expires_from_now(std::chrono::seconds(5));//time to wait need to be changed after testing.
        ptr_t->wait();
		std::cout<<"Re Read"<<std::endl;
	}
	else
	{
		int bagId = -1;
        int depth = -1;//in unit of mm
		int size = filecontent.size();
		std::cout<<"# of lines: "<<size<<std::endl;
		for(int i=1; i<size; i++)
        {
            sscanf(filecontent[i].c_str(),"%d%*c%d",&bagId, &depth);
			if(depth<tmpdepth)
            {
				tmpdepth = depth;
				tmpbag = bagId;
            }
        }

		if(tmpbag==-1&&tmpdepth==DEPTHCUT)//all bags are above DEPTHCUT;
		{
			SendMsg("AllDone50");	
			{
				std::lock_guard<std::mutex> lock1(send_rec);
				f_sent = true;
			}
			cond_CC.notify_one();
			return;
		}

		*lowestDepth = tmpdepth;
		*lowestBag = tmpbag;

		std::cout<<"lowestBag = "<<*lowestBag<<std::endl;
		std::cout<<"lowestDepth = "<<*lowestDepth<<std::endl;

		SendMsg(CreateCMD(COMMAND4PPSTART, *lowestBag));
		{	
			std::lock_guard<std::mutex> lock1(send_rec);
			f_sent = true;
		}
		cond_CC.notify_one();
		std::cout<<"notify receiver"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));///tmp
//		{
			std::unique_lock<std::mutex> lock2(send_rec);
			std::cout<<"StartTimer"<<std::endl;
//			std::shared_ptr<asio::steady_timer> ptr_t1(new asio::steady_timer(*ptr_io));
//			ptr_t1->expires_from_now(std::chrono::seconds(30));//time to wait need to be changed after testing.
//			ptr_t1->async_wait(&ResetCounter);
//			asio::steady_timer t1(*ptr_io);
//			asio::steady_timer t1(*ptr_io, std::chrono::steady_clock::now() + std::chrono::seconds(2));
//			t1.expires_from_now(std::chrono::seconds(2));
//			t1.async_wait(&ResetCounter);
//			toreset = true;//tmp
			std::thread thread1(TimerThread, ptr_io);			
//			thread1.join();
			std::cout<<"f_received = "<<f_received<<" toreset = "<<toreset<<std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(4));
            cond_CC.wait(lock2, []{return f_received||toreset;});
//            cond_CC.wait(lock2, []{return toreset;});

			std::cout<<"CancelTimer"<<std::endl;
//			ptr_t1->cancel();
//			t1.cancel();
//			std::cout<<"CancelTimer"<<std::endl;

            f_sent = false;
            f_received = false;

			if(toreset==true)
			{
				toreset = false;
				SendMsg(CreateCMD(COMMAND4PPSTART+6, 50));
			}
			thread1.join();
            lock2.unlock();
//		}
	}

//	std::this_thread::sleep_for(std::chrono::seconds(1));
	ptr_io->post(std::bind(ReadDepth, ptr_io, fileopen, lowestBag, lowestDepth));
//	return ; 

}


void WorkThread(std::shared_ptr<asio::io_service> ptr_io, std::string fileName, int* lowestBag, int* lowestDepth)
{
	ReadDepth(ptr_io, fileName, lowestBag, lowestDepth);
	ptr_io->run();
}

int main()
{

    std::string inputName = "/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt";//name of output file which stores the measured result

	std::shared_ptr<asio::io_service> ptr_io(new asio::io_service);
//	std::shared_ptr<asio::steady_timer> pt(new asio::steady_timer(*ptr_io));
//	std::shared_ptr<asio::steady_timer> pt(new asio::steady_timer(io));//, std::chrono::seconds(3)));

////////////////////////////////////
/*
	int lowestBag = -1, lowestDepth = 2100;
	ReadDepth(ptr_io, inputName, &lowestBag, &lowestDepth);

	ptr_io->run();
*/
////////////////////////////////////
	

////////////////////////////////////
	int lb =-1, ld = DEPTHCUT;
	int* lowestBag = &lb;
	int * lowestDepth = &ld;// 
	std::vector<std::thread> Threads;

	Threads.emplace_back(std::thread(WorkThread, ptr_io, inputName, lowestBag, lowestDepth));
//	Threads.emplace_back(std::thread(ReceiveMsg));

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }

////////////////////////////////////



//	std::cout<<"lowestBag = "<<lowestBag<<std::endl;
//	std::cout<<"lowestDepth = "<<lowestDepth<<std::endl;

	std::cout<<"finish..."<<std::endl;
	return 0;

}


/*
	readfileand then sendmsg
	waitforreply(stop waiting after certain time and send StopNow50 to piplates.)
	readfileand then send msg
	waitforreply(stop waiting after certain time and send StopNow50 to piplates.)
	...
*/	
 
