#ifndef INTERPRETBAG_PIPPLATE_H
#define INTERPRETBAG_PIPPLATE_H 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "PiPlateSectorBase.h"

// Interpret the board and channel on piplate according to the bag id

int InterpretBag_PiPlate(std::string map, std::vector<std::pair<int, struct_BagBoardChannel>>& BBCmap)
{
    std::ifstream file(map.c_str());
    std::string linecontents;
    int x=-1, y=-1, z=-1;//bag, board, channel
	int iset=-1, ifunc=-1;
    if(file.is_open()){
        int i=0, iset_old=-2;
        while(getline(file,linecontents))
        {
            sscanf(linecontents.c_str(),"%d%*c%d%*c%d%*c%d%*c%d",&iset, &x, &ifunc, &y, &z);
			if(i>0&&iset!=iset_old)
			{
				std::cout<<"There are bags which don't connect to this piplates set. Please check"<<std::endl;
                file.close();
                return -1;
			}
			iset_old = iset;
			if(ifunc<0||ifunc>2)//enum fill-0,purgegas-1,drain-2
			{
				std::cout<<"There are relays whose ifunc are not correct"<<std::endl;
				file.close();
                return -1;
			}
			struct_BagBoardChannel numericMap = {x, y, z};
			std::pair<int, struct_BagBoardChannel> tmpMember(ifunc, numericMap);
			BBCmap.push_back(tmpMember);
            i++;
            if(i>NMAXRELAYS)
            {
                std::cout<<"The map file structure seems not correct. Please check"<<std::endl;
				file.close();
                return -1;
            }
        }
        file.close();
        return 0;
    }
    else
    {
        std::cout<<"Can't open the map"<<std::endl;
        return -1;
    }
}

int InterpretBagwFunc_PiPlate(std::string map, std::vector<struct_BagBoardChannel>& FillBBCmap, std::vector<struct_BagBoardChannel>& PGBBCmap, std::vector<struct_BagBoardChannel>& DrainBBCmap)
{
    std::ifstream file(map.c_str());
    std::string linecontents;
    int x=-1, y=-1, z=-1;//bag, board, channel
	int iset=-1, ifunc=-1;
    if(file.is_open()){
        int i=0, iset_old=-2;
        while(getline(file,linecontents))
        {
            sscanf(linecontents.c_str(),"%d%*c%d%*c%d%*c%d%*c%d",&iset, &x, &ifunc, &y, &z);
			if(i>0&&iset!=iset_old)
			{
				std::cout<<"There are bags which don't connect to this piplates set. Please check"<<std::endl;
                file.close();
                return -1;
			}
			iset_old = iset;
			struct_BagBoardChannel numericMap = {x, y, z};
			if(ifunc==0)
				FillBBCmap.push_back(numericMap);
			else if(ifunc==1)
				PGBBCmap.push_back(numericMap);
			else if(ifunc==2)
                DrainBBCmap.push_back(numericMap);
			else
			{
				std::cout<<"There are relays whose ifunc are not correct"<<std::endl;
				file.close();
                return -1;
			}
            i++;
            if(i>NMAXRELAYS)
            {
                std::cout<<"The map file structure seems not correct. Please check"<<std::endl;
				file.close();
                return -1;
            }
        }
        file.close();
        return 0;
    }
    else
    {
        std::cout<<"Can't open the map"<<std::endl;
        return -1;
    }
}


#endif
