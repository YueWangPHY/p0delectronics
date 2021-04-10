#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>


enum class PortNum{
    CtoPS = 30000,
    CtoPP,
    PStoC,
    PPtoC,
    PStoPP,
    PPtoPS
};


struct struct_BagBoardChannel{

    int bag, board, channel;

};


bool sortstructBBC(struct_BagBoardChannel s1, struct_BagBoardChannel s2);

const int NMAXBAGS = 50;
const int NCMD = 11;
extern std::string COMMANDSTRING[NCMD];//CommandsString[7];//[NCMD];//I don't know why use NCMD here is not ok

const int MAXTIMEDIFF4CMDSENDEXE = 100; //in sec, max time diff btw the time when a command is sent and executed.

const int NMEASUREMENTS = 20;

//const int DEPTHMAXCUT = 1700;//mm
//const int DEPTHMINCUT = 20;//mm // will be comment later

const int NMAXBAGSFILLSIM = 1;
const int NMAXBAGSDRAINSIM = 2;//4;

const int MAXDEPTHDIFF = 110;//in mm

//const int RELAYOPENTIMELENGTH = 40;//20;//in sec// should be moved to piplatesector later

enum { // the index of in COMMANDSTRING;
	COMMAND4PSSTART     = 0,
	COMMAND4PPSTART		= 1,
	COMMAND4PPCLOSESTART = 4,
	COMMAND4CCSTART     = 8,
};

std::string GetCurrentTime();

int GetTimeDifference(std::string t_early, std::string t_late);

std::string CreateCMD(int strId, int bagId);

#endif
