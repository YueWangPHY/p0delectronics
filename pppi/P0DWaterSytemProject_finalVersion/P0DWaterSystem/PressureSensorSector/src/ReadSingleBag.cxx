#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>

#include "config.h"
#include "GlobalBase.h"
#include "ReadPressureSensors.h"
#include "InterpretBag_PS.h"

int main(int argc, char* argv[])
{
    std::cout<<"Hello world"<<std::endl;

	const int num=NMAXBAGS;//num of bags in total

	int iBag =-1; 	//the bag to measure
	int flag=-1;	//mark the index of iBag in the map
	int bags[num],boards[num],channels[num];

	if(sscanf(argv[1],"%d",&iBag)==EOF) 
		throw std::runtime_error("Can't read arguments");	
	if(iBag<1 ||iBag>50)
		throw std::runtime_error("bag not exsit");	

	std::cout<<"iBag="<<iBag<<std::endl;

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

	std::string temp = argv[1];
	std::string outputName = "PressureBag"+temp+".txt";//name of output file which stores the measured result
	std::ofstream * output = new std::ofstream(outputName.c_str()); 

	for(int n=0;n<num;n++)
	{
		if(iBag==bags[n])
		{
			flag = n;
			break;
		}	
			
	//		throw std::runtime_error("can't find the bag in the map");
	}	

    int sleeptime = 1; //in second
    int psBoard = -1, psChannel = -1;   //address of the board and the channel
    int Nmeasure = 100;    //Measure Nmeasure times and take the average

    psBoard = boards[flag]+0x70;    //address of the board
    psChannel = channels[flag];     //address of the channel

	int countbreak = 0;
    while(true){
        int cnt=0;
		countbreak++;
		if(countbreak>10)
			break;
        double avePress=0, aveTemp=0;
		ReadDepthTemp(psBoard,psChannel,Nmeasure, avePress,aveTemp);

        std::cout<<"Bag = "<<iBag<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
		(*output)<<"Bag = "<<iBag<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
        sleep(sleeptime);
    }



  return 0;

}
