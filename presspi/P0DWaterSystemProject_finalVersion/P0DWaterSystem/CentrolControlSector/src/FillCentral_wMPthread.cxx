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

int DepthMeausureThread(std::string depthfile)
{
    const int num=NMAXBAGS;//num of bags in total
    int bags[num],boards[num],channels[num];
    int Nmeasure = 20;  //Measure Nmeasure times and take the average
    int sleeptime =1;   //in second
	
	std::string filepath = depthfile;

    std::string map_BagBoardChannel;
    if(GetPSBagBoardChannelMap(map_BagBoardChannel))
        std::cout<<"the map in cxx is "<<map_BagBoardChannel<<std::endl;
    else
    {
        std::cout<<"NO MAP"<<std::endl;
        return 0;
    }

    std::ifstream ftest(map_BagBoardChannel.c_str());


    if(!ftest.is_open())
        std::cout<<"can't find"<<std::endl;

    InterpretBag_PS(map_BagBoardChannel,bags,boards,channels);

    std::ofstream outAllTimeMeasure("StoreDepthofAllBags.txt");
    int filefd;
    struct flock flk;
    int counter = 0;
    while(true)
    {
        filefd = open(filepath.c_str(), O_RDWR);//("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt", O_RDWR);
//        filefd = open("/home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/macro/depth_fillcentral.txt", O_RDWR);

        if(filefd<0)
        {
            std::cout<<"In AllBagDepth: filefd<0, please check!!!"<<std::endl;
            continue;
        }

        flk.l_type = F_WRLCK;
        flk.l_whence = SEEK_SET;
        flk.l_start = 0;
        flk.l_len = 0;
        fcntl(filefd, F_SETLKW, &flk);
        std::cout<<"inlock"<<std::endl;

        std::ofstream  output(filepath.c_str());//"/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt") ;

        std::string stringtime = GetCurrentTime();

        output<<stringtime<<std::endl;
        std::cout<<stringtime<<std::endl;
        outAllTimeMeasure<<stringtime<<std::endl;
        //measure depth and write into the file
        for(int i=0;i<50;i++)//num
        {
            double avePress=0, aveTemp=0;
            int psBoard = boards[i]+0x70;
            int psChannel = channels[i];

            ReadDepthTemp(psBoard, psChannel, Nmeasure, avePress, aveTemp);

            std::string strbagid = std::to_string(bags[i]);
            std::string strdepth = std::to_string((int)PressureToDepthConversion(avePress));
            output<<std::setw(2)<<bags[i]<<" "<<std::setw(4)<<avePress<<std::endl;//in mm
//(int)PressureToDepthConversion(avePress)<<std::endl;//depth in mm
            std::cout<<"Bag = "<<bags[i]<<" , Depth = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;

            outAllTimeMeasure<<"Bag = "<<bags[i]<<" , Depth = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
        }

        flk.l_type = F_UNLCK;
        fcntl(filefd, F_SETLKW, &flk);
        close(filefd);
        std::cout<<"Out of lock"<<std::endl;

        //change rest time between readings here
		sleep(5);
    }
    return 0;


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
//    std::shared_ptr<CentralAction> pAction(new CentralAction(ps, pr, 1, filepath, fillupto));//to fill set 1
    std::shared_ptr<CentralAction> pAction(new CentralAction(ps, pr, 0, filepath, fillupto));//to do nthing set 0


    std::shared_ptr<asio::io_service> io_service_operation(new asio::io_service);
    std::vector<std::thread> Threads;

    Threads.emplace_back(std::thread(&CentralAction::CentralReceiveAction, pAction));
	Threads.emplace_back(std::thread(CallCentralOperation, pAction, io_service_operation));
	Threads.emplace_back(std::thread(DepthMeausureThread, filepath));
//    Threads.emplace_back(std::thread(CallCentralOperation, pAction, io_service_operation));//to test give to threads of operation.

    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }


    std::cout<<"finish..."<<std::endl;
	return 0;
}
