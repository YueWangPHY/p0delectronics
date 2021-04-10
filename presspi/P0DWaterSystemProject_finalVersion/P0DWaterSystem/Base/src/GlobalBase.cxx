#include "GlobalBase.h"

std::string COMMANDSTRING[NCMD]={   "MSPress",
                                    "FillBag",// 1 to 7 for PP
                                    "PurgGas",
                                    "DraiBag",
                                    "ClsFBag",//close all filling relay of the bag
                                    "ClsPBag",
                                    "ClsDBag",
                                    "StopNow",
                                    "DepthIs",//not used // rest for CentralControl
                                    "DoneBag",
                                    "AllDone" };


bool sortstructBBC(struct_BagBoardChannel s1, struct_BagBoardChannel s2)
{
    return s1.bag<s2.bag;
}

std::string GetCurrentTime()
{
    auto current = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(current);

    std::tm *current_tm = std::localtime(&current_time);

    char buff[20];

    if(std::strftime(buff,20, "%m%d%H%M%S",current_tm)!=10)
        return "";
    return buff;

}


int GetTimeDifference(std::string t_early, std::string t_late)
{
    int diff = -1;
    std::string date1 = t_early.substr(0, 4);
    std::string date2 = t_late.substr(0, 4);
    std::string timemin1 = t_early.substr(4,2);
    std::string timesec1 = t_early.substr(6,2);
    std::string timemin2 = t_late.substr(4,2);
    std::string timesec2 = t_late.substr(6,2);
//    std::string time1 = t_early.substr(4);
//    std::string time2 = t_late.substr(4);
    if(date1!=date2)
        return -1;
   
    try{
//        int time_1 = std::stoi(time1);
//        int time_2 = std::stoi(time2);
        int time_1 = std::stoi(timemin1)*60+std::stoi(timesec1);
        int time_2 = std::stoi(timemin2)*60+std::stoi(timesec2);
        diff = time_2-time_1;
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return diff;//diff should be >=0 if time format is correct.

}

std::string CreateCMD(int strId, int bagId)
{
	std::string time = GetCurrentTime();
	std::string cmd_str = COMMANDSTRING[strId];
	std::string bag_str = "";
	if(bagId<0)
		bagId = 0;//don't know if correct
	if(bagId<10&&bagId>=0)
		bag_str = "0"+std::to_string(bagId);
	else 
		bag_str = std::to_string(bagId);
	
	return time+cmd_str+bag_str;
}

