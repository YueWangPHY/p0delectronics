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

#include "config.h"
#include "GlobalBase.h"
#include "ReadPressureSensors.h"
#include "InterpretBag_PS.h"
#include "CentralBase.h"
#include "PiPlateSectorBase.h"

int main(int argc, char* argv[])
{
	// becuase the function GetCurrentTime don't give us the year and the gac happens to need year info, so getthe year here instead of in every loop as it's unlikely that the year will change when the program is running. Even in that case, restarting the program solves the issue easliy. 
    auto current = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(current);
    std::tm *currenttm = std::localtime(&current_time);
	int currentyear = currenttm->tm_year + 1900;
	//

	const int num=NMAXBAGS;//num of bags in total
	int bags[num],boards[num],channels[num];
	int Nmeasure = 20;	//Measure Nmeasure times and take the average
    int measperiod = 5;//5sec in default
	std::string storepath="";

    if(argc>1)
        sscanf(argv[1], "%d", &measperiod);
	if(argc>2)
	{
		storepath=argv[2];
		int strsize = sizeof(argv[2]);
		if(argv[2][strsize-1]!='/') //check if the path is ended is "/"
			storepath = storepath + "/"; //If not, add it to make sure the file stored in the assigned path
	}
	std::cout<<argv[2]<<std::endl;
	std::cout<<"measperiod = "<<measperiod<<std::endl;
	std::cout<<"storepath = "<<storepath<<std::endl;

	if(measperiod>=30)// as measuring all 50 bags with 20 times each cost about 2s. SO when measperiod is small, use a smaller Nmeasure. When measperiod goes high which will usually be the case of monitoring depth, use a larger Nmeasure to improve the stability becuase the time won't constrain us.
		Nmeasure = 100;
	if(measperiod>RELAYOPENTIMELENGTH)
		std::cout<<"The measuring period is longer than the relay opening time. If you are doing filling process instead monitoring, please notice this because the measured value could be not update due to the long period"<<std::endl;


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

	std::string startingtime = GetCurrentTime();
	std::cout<<startingtime<<std::endl;
	std::string starthour = startingtime.substr(0, 6);
	std::string storename = storepath+"StoreDepthofAllBags_"+starthour+".txt";
	
	std::string forgscname = storepath+"currentWaterdepth.dat";

	std::ofstream outAllTimeMeasure;
	std::ofstream outforgsc;

	int filefd;
	struct flock flk;
	int counter = 0;
	std::string filepath="";
	if(!GetPSReadingfile(filepath))
    {
        std::cout<<filepath<<std::endl;
        std::cout<<"Can't file depth file"<<std::endl;
        return -1;
    }

	double BagsPressure[num];
	double BagsTemperaure[num];
	for(int i=0;i<num;i++)
	{
		BagsPressure[i]=-999.0;
		BagsTemperaure[i]=-999.0;
	}
	

	while(true)
	{
		std::string stringtime = GetCurrentTime();
		// measure depth
		for(int i=0;i<num;i++)
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
			BagsPressure[i] = avePress;
			BagsTemperaure[i] = aveTemp;
		}

		outAllTimeMeasure.open(storename.c_str(), std::ofstream::out | std::ofstream::app);	
		outforgsc.open(forgscname.c_str(), std::ofstream::out);
		filefd = open(filepath.c_str(), O_RDWR);

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

		std::ofstream  output(filepath.c_str());

	
		//output
		output<<stringtime<<std::endl;
		std::cout<<stringtime<<std::endl;
		outAllTimeMeasure<<stringtime<<std::endl;
		outforgsc<<currentyear<<stringtime<<std::endl; 

		//write into the file
		for(int i=0;i<num;i++)//num
		{
			std::string strbagid = std::to_string(bags[i]);
			std::string strdepth = std::to_string((int)PressureToDepthConversion(BagsPressure[i]));				
			output<<std::setw(2)<<bags[i]<<" "<<std::setw(4)<<(int)PressureToDepthConversion(BagsPressure[i])<<std::endl;//depth in mm
			outforgsc<<std::setw(2)<<bags[i]<<" "<<std::setw(4)<<(int)PressureToDepthConversion(BagsPressure[i])<<std::endl;
			std::cout<<"Bag = "<<bags[i]<<" , Depth = "<<(int)PressureToDepthConversion(BagsPressure[i])<<" , Pressure = "<<BagsPressure[i]<<" , Temperature = "<<BagsTemperaure[i]<<std::endl;
			outAllTimeMeasure<<"Bag = "<<bags[i]<<" , Depth = "<<(int)PressureToDepthConversion(BagsPressure[i])<<" , Pressure = "<<BagsPressure[i]<<" , Temperature = "<<BagsTemperaure[i]<<std::endl;

		}

		flk.l_type = F_UNLCK;
		fcntl(filefd, F_SETLKW, &flk);
		close(filefd);
		std::cout<<"Out of lock"<<std::endl;
		
		outforgsc.close();
		outAllTimeMeasure.close();

		sleep(measperiod);
	}

	return 0;
}


