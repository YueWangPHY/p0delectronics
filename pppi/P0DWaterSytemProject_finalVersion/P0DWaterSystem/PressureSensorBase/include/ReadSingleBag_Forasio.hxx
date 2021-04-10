#ifndef READSINGLEBAG_FORASIO
#define READSINGLEBAG_FORASIO

 
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

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

#ifndef map_BagBoardChannel
#define map_BagBoardChannel "/home/pi/PressureSensorProject/PressureSensor/macro/map_BagBoardChannel.txt"
#endif

#include "ReadPressureSensors.h"

	double ReadSingleBag_Forasio(int bagnum);
/*
//int ReadSingleBag_Forasio(int bagnum)
double ReadSingleBag_Forasio(int bagnum)
{
    std::cout<<"Hello world from ReadSigne"<<std::endl;

    const int num=50;//num of bags in total

    int iBag =-1;   //the bag to measure
    int flag=-1;    //mark the index of iBag in the map
    int bags[num],boards[num],channels[num];

    iBag = bagnum;
//  if(sscanf(argv[1],"%d",&iBag)==EOF)
//      throw std::runtime_error("Can't read arguments");
    if(iBag<1 ||iBag>50)
        throw std::runtime_error("bag not exsit");

    std::cout<<"iBag="<<iBag<<std::endl;

    std::ifstream ftest(map_BagBoardChannel);

    if(!ftest.is_open())
        std::cout<<"can't find"<<std::endl;

    InterpretBags(map_BagBoardChannel,bags,boards,channels);

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

    //      throw std::runtime_error("can't find the bag in the map");
    }

    int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");

    int sleeptime = 1; //in second
    int psBoard = -1, psChannel = -1;   //address of the board and the channel
    int Nmeasure = 1000;    //Measure Nmeasure times and take the average

    psBoard = boards[flag]+0x70;    //address of the board
    psChannel = channels[flag];     //address of the channel

//    while(true){
        int cnt=0;
        double avePress=0, aveTemp=0;
        while(cnt<Nmeasure){
            cnt++;
            double iPress=0, iTemp=0;
            if(!ReadPS(fd,psBoard,psChannel,iPress,iTemp))
                throw std::runtime_error("Error reading sensor");
            avePress += iPress;
            aveTemp += iTemp;
        }
        avePress = avePress/(double)Nmeasure;
        aveTemp = aveTemp/(double)Nmeasure;

//      std::cout<<"Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;

        std::cout<<"Bag = "<<iBag<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
        (*output)<<"Bag = "<<iBag<<" , Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
//        sleep(sleeptime);
//    }

  if (close(fd) < 0) {
      throw std::runtime_error("Can't close the i2c bus");
  }

//  return 0;
	return avePress;
}
*/


#endif
