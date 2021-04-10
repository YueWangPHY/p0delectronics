#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define PiPlateUsed
#define PPBagBoardChannelMap /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/PiPlateSector/macro/map_BagPiPlateBoardChannel.txt

/* #undef PressSensorUsed */
/* #undef PSBagBoardChannelMap */

/* #undef PSReadFile */


bool GetPSBagBoardChannelMap(std::string& location)
{
#ifdef PSBagBoardChannelMap
	location = "";
    return 1;
#else
    return 0;
#endif
}

bool GetPPBagBoardChannelMap(std::string& location)
{
#ifdef PPBagBoardChannelMap
	location = "/home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/PiPlateSector/macro/map_BagPiPlateBoardChannel.txt";
    return 1;
#else
    return 0;
#endif
}

bool GetPSReadingfile(std::string& location)
{
#ifdef PSReadFile
	location = "";
	return 1;
#else
	return 0;
#endif
}

#endif


