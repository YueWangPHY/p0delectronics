#ifndef INTERPRETBAG_PS_H
#define INTERPRETBAG_PS_H 

#include <iostream>
#include <string>
#include <vector>

//#include "Basic.h"
#include "GlobalBase.h"
#include "config.h"

// Interpret the board and channel on Pressure Sensor boards from the map

int InterpretBag_PS(std::string map, int* gbags, int* gboards, int* gchannels)
{
    std::ifstream file(map.c_str());//("map_BagBoardChannel.txt");//(map.c_str());
    std::string linecontents;
    if(file.is_open()){
        int i=0;
		while(i<NMAXBAGS)
        {
            getline(file,linecontents);
            sscanf(linecontents.c_str(),"%d%*c%d%*c%d",&gbags[i],&gboards[i],&gchannels[i]);
            i++;
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

int InterpretBag3D_PS(std::string map, struct_BagBoardChannel* numericMap)
{
	std::ifstream file(map.c_str());//("map_BagBoardChannel.txt");//(map.c_str());
    std::string linecontents;
	int x=-1, y=-1, z=-1;
    if(file.is_open()){
        int i=0;
		while(getline(file,linecontents))
        {
            sscanf(linecontents.c_str(),"%d%*c%d%*c%d",&x, &y, &z);
			numericMap[i] = {x, y, z};
            i++;
			if(i>NMAXBAGS)
			{
				std::cout<<"file structure seems not correct. Please check"<<std::endl;
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

std::pair<int, int> FindPSBoardChannelofBag(std::string map, int ibag)
{
    std::pair<int, int> BoardChannel(-1,-1);
    int bags[NMAXBAGS], boards[NMAXBAGS], channels[NMAXBAGS];
    InterpretBag_PS(map,bags,boards,channels);// think about pair<bag, pair<board,channel>> and then sort bag.
                                            // sort(): N*log2(N), lop below:N^2. But considering 50 is not big, so keep it as it is now???
    for(int i=0;i<NMAXBAGS;i++)
    {
        if(bags[i]==ibag)
        {
            BoardChannel.first = boards[i];
            BoardChannel.second = channels[i];
            break;
        }

    }

    return BoardChannel;
}

#endif
