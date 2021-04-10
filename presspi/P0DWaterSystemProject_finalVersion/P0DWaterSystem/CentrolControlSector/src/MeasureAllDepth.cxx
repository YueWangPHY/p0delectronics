#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

#include "config.h"
#include "ReadPressureSensors.h"
#include "InterpretBag_PS.h"
#include "CentralBase.h"
#include "MeasureAllDepth.h"

//int main()
int MeasureAllDepth()
{
	const int num=NMAXBAGS;//num of bags in total
	int bags[num],boards[num],channels[num];
	int Nmeasure = 20;	//Measure Nmeasure times and take the average
	int sleeptime =1;	//in second

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

    int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");

//	std::ofstream * output = new std::ofstream("PressureofAllBags.txt");
	int counter = 0;
	while(true)
	{
		{
			std::lock_guard<std::mutex> lock1(lockfile);
			std::cout<<"inlock"<<std::endl;
			std::ofstream  output("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt") ;//= new std::ofstream("PressureofAllBags.txt");
/*
			if(!output.is_open())
			{
				std::cout<<"WARNING!!! Can't write the water depth"<<std::endl;
				continue;
			}
*/
			if(output.is_open())
			{
				output<<GetCurrentTime()<<std::endl;			
				std::cout<<GetCurrentTime()<<std::endl;
				for(int i=0;i<50;i++)//num
				{
					int cnt=0;
					double avePress=0, aveTemp=0;
					int	psBoard = boards[i]+0x70;
					int	psChannel = channels[i];
					while(cnt<Nmeasure)
					{
						cnt++;
						double iPress=0, iTemp=0;
						if(!ReadPS(fd,psBoard,psChannel,iPress,iTemp))
							throw std::runtime_error("Error reading sensor");
						avePress += iPress;
						aveTemp += iTemp;
					}
					avePress = avePress/(double)Nmeasure;
					aveTemp = aveTemp/(double)Nmeasure;
					
					output<<std::setw(2)<<bags[i]<<" "<<std::setw(4)<<(int)PressureToDepthConversion(avePress)<<std::endl;//depth in mm
					std::cout<<"Bag = "<<bags[i]<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<std::endl;
	//	        	std::cout<<"Bag = "<<bags[i]<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Pressure = "<<avePress<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Temperature = "<<aveTemp<<std::endl;
				}
			}
			output.close();
		}
		std::cout<<"out of lock"<<std::endl;
		sleep(2);
	}
	return 0;
}















