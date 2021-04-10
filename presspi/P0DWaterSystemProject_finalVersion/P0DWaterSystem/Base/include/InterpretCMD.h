#ifndef INTERPRETCOMMAND_H
#define INTERPRETCOMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include "GlobalBase.h"

	
std::pair<int, int> InterpretCMD(std::string cmd)
{
	std::pair<int, int> command(-1, -1);
	
	//command format is datetime+comandstr+bagid. It is exactly 19 digits
	if(cmd.size()!=19)
		return command;	

	std::string cmdDateTime = cmd.substr(0, 10);
	std::string cmdString = cmd.substr(10,7);	
	std::string cmdBagID = cmd.substr(17);

	//Compare current time with the time when the command was sent. 
	//If the time difference is larger than certain time, then the command received will be considered nvalid. 

	std::string currentDateTime = GetCurrentTime();
	if(GetTimeDifference(cmdDateTime,currentDateTime)<0||GetTimeDifference(cmdDateTime,currentDateTime)>MAXTIMEDIFF4CMDSENDEXE)//in sec, treat the received cmd invalid
		return command;

	//check whether bag is valid
	int bagID = -1;
	std::string::size_type sz;
	try{
		bagID = std::stoi(cmdBagID,&sz);//If no conversion could be performed, an invalid_argument exception is thrown by stof.
	}
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

	std::string restofcmd = cmdBagID.substr(sz);
	if(!restofcmd.empty())
		return command;

	if(bagID<1||bagID>NMAXBAGS)//bag counts from 1 to NMAXBAGS
		return command;

	//check if cmd is valid

    int cmdstrID = -1;
	for(int i=0;i<NCMD;i++)
	{
		if(cmdString == COMMANDSTRING[i])
			cmdstrID = i;
	}
	if(cmdstrID==-1)
		return command;
	else
	{
		command.first = cmdstrID;
		command.second = bagID;
	}
	
	return command;

}

#endif
