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

#include "config.h"
#include "ReadPressureSensors.h"



int main(int argc, char* argv[])
{
    std::cout<<"Hello world"<<std::endl;

	std::string board = argv[1];
	std::string channel = argv[2];
	std::string outputName = "Pressure"+ board + "_" + channel+ ".txt";
	std::ofstream * output = new std::ofstream(outputName.c_str());

    int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");

    int sleeptime = 1; //in second
    int psBoard = -1, psChannel = -1;   //address of the board and the channel
    int Nmeasure = 1000;    //Measure Nmeasure times and take the average

    psBoard = std::stoi(board)+0x70;    //address of the board
    psChannel = std::stoi(channel);     //address of the channel

    while(true){
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

        std::cout<<"Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
		(*output)<<"Board = "<<psBoard-0x70<<" , Channel = "<<psChannel<<" , Depth = "<<(int)PressureToDepthConversion(avePress)<<" , Pressure = "<<avePress<<" , Temperature = "<<aveTemp<<std::endl;
        sleep(sleeptime);
    }

  if (close(fd) < 0) {
      throw std::runtime_error("Can't close the i2c bus");
  }

  return 0;

}
