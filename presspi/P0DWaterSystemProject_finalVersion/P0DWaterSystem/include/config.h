#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define PiPlateUsed
#define PPBagBoardChannelMap /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PiPlateSector/macro/map_BagPiPlateBoardChannel.txt

#define PressSensorUsed
#define PSBagBoardChannelMap /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorSector/macro/map_BagPressSensorBoardChannel.txt

#define PSReadFile /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/macro/depth_fillcentral.txt


bool GetPSBagBoardChannelMap(std::string& location)
{
#ifdef PSBagBoardChannelMap
	location = "/home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorSector/macro/map_BagPressSensorBoardChannel.txt";
    return 1;
#else
    return 0;
#endif
}

bool GetPPBagBoardChannelMap(std::string& location)
{
#ifdef PPBagBoardChannelMap
	location = "/home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PiPlateSector/macro/map_BagPiPlateBoardChannel.txt";
    return 1;
#else
    return 0;
#endif
}

bool GetPSReadingfile(std::string& location)
{
#ifdef PSReadFile
	location = "/home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/macro/depth_fillcentral.txt";
	return 1;
#else
	return 0;
#endif
}

#endif


