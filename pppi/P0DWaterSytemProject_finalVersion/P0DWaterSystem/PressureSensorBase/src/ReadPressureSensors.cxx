#include <linux/i2c-dev.h>

#include <fcntl.h>
#include <unistd.h>

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <string>

#include "ReadPressureSensors.h"

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

int ReadPS_new(int board, int channel, double& pressure, double& temperature)
{
    unsigned char buffer[32]={0};
    int len=0;

	int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");


    if(ioctl(fd, I2C_SLAVE,board)<0)
        throw std::runtime_error("Can't access the i2c slave address");

    buffer[0] = (unsigned char)board; // I2C Switch Addr on Selected Board
    buffer[1] = 1;
    buffer[1] = buffer[1] << (unsigned char)channel ; // Open Selected Channel
    len = 2;
    if(write(fd,buffer,len)!=len)
        throw std::runtime_error("Can't write to the i2c bus");

	// *************************************************************

    buffer[0] = 0;//I think this part is just to test. Code should work if without this part
    buffer[1] = 0;
    buffer[2] = 0;
    len = 1;
    if(read(fd,buffer,len)!=len)
        throw std::runtime_error("Can't read from the i2c switch");

	// *************************************************************

    int addr = 0x28;//addr of pressure sensors
    if(ioctl(fd,I2C_SLAVE,addr)<0)
        throw std::runtime_error("Can't access the pressure sensors");

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    len = 4;

    int res = read(fd,buffer,len);
    int measureP,measureT;
    double appliedP,appliedT;
    if(res!=len)
        std::cout<<"Something is wrong with this pressure sensor"<<std::endl;
    else{
//  std::cout<<"buffer[0]= "<<buffer[0]<<"  buffer[1]= "<<buffer[1]<<" buffer[2]= "<<buffer[2]<<" buffer[3]= "<<buffer[3]<<std::endl;
        measureP = buffer[0] & 0x3F;    // Strip out Status Bits
        measureP = (measureP << 8) | buffer[1];

        measureT = buffer[3] >> 5;
        measureT = measureT | ( buffer[2] << 3 );

        appliedP = PSOutputPressConversion((double) measureP);
        appliedT = PSOutputTemConversion((double) measureT);
    }

    pressure = appliedP;
    temperature = appliedT;

    if(ioctl(fd, I2C_SLAVE,board)<0)
        throw std::runtime_error("Can't access the i2c slave address");

    // Turn OFF All I2C Switches
    buffer[0] = (unsigned char)board; // I2C Switch Addr on Selected Board
    buffer[1] = 0 ;     // Turn OFF All Channels
    len = 2;

    if(write(fd,buffer,len)!=len)
        throw std::runtime_error("Can't write to the i2c bus");

	if (close(fd) < 0) 
      throw std::runtime_error("Can't close the i2c bus");

    return 1;

}


int ReadPS(int fd,int board, int channel, double& pressure, double& temperature)
{
    unsigned char buffer[32]={0};
    int len=0;

    if(ioctl(fd, I2C_SLAVE,board)<0)
        throw std::runtime_error("Can't access the i2c slave address");

    buffer[0] = (unsigned char)board; // I2C Switch Addr on Selected Board
    buffer[1] = 1;
    buffer[1] = buffer[1] << (unsigned char)channel ; // Open Selected Channel
    len = 2;
    if(write(fd,buffer,len)!=len)
        throw std::runtime_error("Can't write to the i2c bus");

	// *************************************************************
/*
    buffer[0] = 0;//I think this part is just to test. Code should work if without this part
    buffer[1] = 0;
    buffer[2] = 0;
    len = 1;
    if(read(fd,buffer,len)!=len)
        throw std::runtime_error("Can't read from the i2c switch");
*/
	// *************************************************************

    int addr = 0x28;//addr of pressure sensors
    if(ioctl(fd,I2C_SLAVE,addr)<0)
        throw std::runtime_error("Can't access the pressure sensors");

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    len = 4;

    int res = read(fd,buffer,len);
    int measureP,measureT;
    double appliedP,appliedT;
    if(res!=len)
        std::cout<<"Something is wrong with this pressure sensor"<<std::endl;
    else{
//  std::cout<<"buffer[0]= "<<buffer[0]<<"  buffer[1]= "<<buffer[1]<<" buffer[2]= "<<buffer[2]<<" buffer[3]= "<<buffer[3]<<std::endl;
        measureP = buffer[0] & 0x3F;    // Strip out Status Bits
        measureP = (measureP << 8) | buffer[1];

        measureT = buffer[3] >> 5;
        measureT = measureT | ( buffer[2] << 3 );

        appliedP = PSOutputPressConversion((double) measureP);
        appliedT = PSOutputTemConversion((double) measureT);
    }

    pressure = appliedP;
    temperature = appliedT;

    if(ioctl(fd, I2C_SLAVE,board)<0)
        throw std::runtime_error("Can't access the i2c slave address");

    // Turn OFF All I2C Switches
    buffer[0] = (unsigned char)board; // I2C Switch Addr on Selected Board
    buffer[1] = 0 ;     // Turn OFF All Channels
    len = 2;

    if(write(fd,buffer,len)!=len)
        throw std::runtime_error("Can't write to the i2c bus");
    return 1;

}


//in PSI
double PSOutputPressConversion(double measurement)
{
   
    double MaxP = 5.0;       // Max Pressure - PSI
    double MinP = 0.0;       // Min Pressure - PSI
    double MaxCnts = 14745;  // 90% of 2^14 (0x3999)
    double MinCnts =  1638;  // 10% of 2^14 (0x0666)

    double pressure=-9999.0;
    pressure=(measurement-MinCnts)*(MaxP-MinP)/(MaxCnts-MinCnts)+MinP;
    return pressure;
}

//in Celsius
double PSOutputTemConversion(double measurement)
{
    return measurement*200.0/2047.0-50.0;
}


//in mm
double PressureToDepthConversion(double measuredPSI)
{
    double PSIToPa = 6894.757;
    double waterdensity = 997;//in kg/m^3
    double gravityacc = 9.8;//in(m/s^2)
    double depth = measuredPSI*PSIToPa/(waterdensity*gravityacc);//in m

	return depth*1000;//in mm

}

//in mm
double MeasureDepth(int board, int channel, int NPSMeasure)//(int iBag);//As we read the same sensor for multiple times and use the averag value as the measured valued, NPSMeasure means how many time to measure before getting ave
{
    int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");

    int psBoard = board+0x70;    //address of the board
    int psChannel = channel;     //address of the channel

    int cnt=0;
	double avePress=0, aveTemp=0;
    while(cnt<NPSMeasure)
    {
		double iPress=0, iTemp=0;
		if(!ReadPS(fd,psBoard,psChannel,iPress,iTemp))
			throw std::runtime_error("Error reading sensor");
		avePress += iPress;
		aveTemp += iTemp;
		cnt++;
    }
	avePress = avePress/NPSMeasure;
	aveTemp = aveTemp/NPSMeasure;

	if (close(fd) < 0) {
		throw std::runtime_error("Can't close the i2c bus");
	}

	return PressureToDepthConversion(avePress);
}

int ReadDepthTemp(int board, int channel, int NPSMeasure, double& depth, double& temp)
{
    int fd = open(I2C_DEVICE,O_RDWR);
    if(fd<0)
        throw std::runtime_error("Can't open the i2c bus");

    int psBoard = board+0x70;    //address of the board
    int psChannel = channel;     //address of the channel

    int cnt=0;
	double avePress=0, aveTemp=0;
    while(cnt<NPSMeasure)
    {
		double iPress=0, iTemp=0;
		if(!ReadPS(fd,psBoard,psChannel,iPress,iTemp))
			throw std::runtime_error("Error reading sensor");
		avePress += iPress;
		aveTemp += iTemp;
		cnt++;
    }
	avePress = avePress/NPSMeasure;
	aveTemp = aveTemp/NPSMeasure;

	if (close(fd) < 0) {
		throw std::runtime_error("Can't close the i2c bus");
	}

	depth = PressureToDepthConversion(avePress);
	temp = aveTemp;
	
	return 0;
}
