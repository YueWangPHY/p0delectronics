#ifndef READPRESSURESENSORS_H
#define READPRESSURESENSORS_H

#include <linux/i2c-dev.h>

#include <fcntl.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif

	int ReadPS(int fd,int board, int channel, double& pressure, double& temperature);	//Read the pressure sensor correspond to the board and channel  
	int ReadPS_new(int board, int channel, double& pressure, double& temperature);//when thigns get stable, use this to replce the readps above	
	
	double PSOutputPressConversion(double measurement);	//convert the measured value to pressure in PSI

	double PSOutputTemConversion(double measurement);	//convert the measured value to temperature in celcius

	double PressureToDepthConversion(double pressure);

	double MeasureDepth(int board, int channel, int NPSMeasure);//ReadPS for NPSMeasure times and convert it to the depth and return the depth. 

	int ReadDepthTemp(int board, int channel, int NPSMeasure, double& depth, double& temp); //return -1 if reading has reported some error
	
#ifdef __cplusplus
}
#endif



#endif
