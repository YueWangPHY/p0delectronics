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

//#ifndef I2C_DEVICE
//#define I2C_DEVICE "/dev/i2c-1"
//#endif

#include "config.h"
#include "ReadPressureSensors.h"
#include "InterpretBag_PS.h"
#include "CentralBase.h"

int main()
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

	std::ofstream outAllTimeMeasure("StoreDepthofAllBags.txt");
	int filefd;
	struct flock flk;
	int counter = 0;
	while(true)
	{
		filefd = open("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt", O_RDWR);

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

		std::ofstream  output("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt") ;

		std::string stringtime = GetCurrentTime();
/*
		write(filefd, stringtime.c_str(), 10);
		write(filefd, "\n", 1);
*/	
		output<<stringtime<<std::endl;
		std::cout<<stringtime<<std::endl;
		outAllTimeMeasure<<stringtime<<std::endl;
		//measure depth and write into the file
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
//				if(!ReadPS(fd,psBoard,psChannel,iPress,iTemp))
				if(!ReadPS_new(psBoard,psChannel,iPress,iTemp))
					throw std::runtime_error("Error reading sensor");
				avePress += iPress;
				aveTemp += iTemp;
			}
			avePress = avePress/(double)Nmeasure;
			aveTemp = aveTemp/(double)Nmeasure;

			std::string strbagid = std::to_string(bags[i]);
			std::string strdepth = std::to_string((int)PressureToDepthConversion(avePress));				
			int bagidlen = strbagid.length();
			int depthlen = strdepth.length();
/*
			write(filefd, strbagid.c_str(), bagidlen);
			write(filefd, " ", 1);
			write(filefd, strdepth.c_str(), depthlen);
			write(filefd, "\n", 1);
*/
			output<<std::setw(2)<<bags[i]<<" "<<std::setw(4)<<(int)PressureToDepthConversion(avePress)<<std::endl;//depth in mm
			std::cout<<"Bag = "<<bags[i]<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
//	        	std::cout<<"Bag = "<<bags[i]<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Pressure = "<<avePress<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Temperature = "<<aveTemp<<std::endl;

			outAllTimeMeasure<<"Bag = "<<bags[i]<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
//			sleep(1);
		}

		flk.l_type = F_UNLCK;
		fcntl(filefd, F_SETLKW, &flk);
		close(filefd);
		std::cout<<"Out of lock"<<std::endl;
		//change rest time between readings here
	sleep(5);

//		sleep(60);
	}
	return 0;
}

















