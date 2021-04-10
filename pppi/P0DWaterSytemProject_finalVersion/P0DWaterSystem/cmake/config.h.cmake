#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#cmakedefine PiPlateUsed
#cmakedefine PPBagBoardChannelMap @PPBagBoardChannelMap@

#cmakedefine PressSensorUsed
#cmakedefine PSBagBoardChannelMap @PSBagBoardChannelMap@

#cmakedefine PSReadFile @PSReadFile@


bool GetPSBagBoardChannelMap(std::string& location)
{
#ifdef PSBagBoardChannelMap
	location = "@PSBagBoardChannelMap@";
    return 1;
#else
    return 0;
#endif
}

bool GetPPBagBoardChannelMap(std::string& location)
{
#ifdef PPBagBoardChannelMap
	location = "@PPBagBoardChannelMap@";
    return 1;
#else
    return 0;
#endif
}

bool GetPSReadingfile(std::string& location)
{
#ifdef PSReadFile
	location = "@PSReadFile@";
	return 1;
#else
	return 0;
#endif
}

#endif


