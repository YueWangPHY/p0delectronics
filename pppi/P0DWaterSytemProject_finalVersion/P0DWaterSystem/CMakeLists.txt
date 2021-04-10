cmake_minimum_required(VERSION 2.6)
set(CMAKE_INSTALL_PREFIX "../build")
project(P0DWaterSystemProject)

#message("CMAKE_CXX_FLAGS" "${CMAKE_CXX_FLAGS})
#message("CMAKE_CXX_FLAGS" "${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_FLAGS "-std=c++11")

option(PressSensorUsed "Use PressureSensors" OFF)
option(PiPlateUsed "Use PiPlates" ON)

#have to make it more elegant later, such as autmatically add suffix to those name and set the path
set(BASE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Base)
set(RELAYBASE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RelayBase)
set(PIPLATESECTOR_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PiPlateSector)
set(PSENSORBASE_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PressureSensorBase)
set(PSENSORSECTOR_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PressureSensorSector)
set(CENTRAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CentrolControlSector)

set(PACKAGE_STATICLIB_LIST)

message(${PSENSORSECTOR_SOURCE_DIR})
if(PressSensorUsed)
    find_path(BBCMAP NAMES map_BagPressSensorBoardChannel.txt
						HINTS "${PSENSORSECTOR_SOURCE_DIR}" "${PSENSORSECTOR_SOURCE_DIR}/macro")
    set(PSBagBoardChannelMap "${BBCMAP}/map_BagPressSensorBoardChannel.txt")
    message(STATUS "PSBagBoardChannelMap: " ${PSBagBoardChannelMap})
endif()

if(PressSensorUsed)
	find_path(PSREAD NAMES depth_fillcentral.txt
						HINTS "${CENTRAL_SOURCE_DIR}" "${CENTRAL_SOURCE_DIR}/macro")
	set(PSReadFile ${PSREAD}/depth_fillcentral.txt)
	message(STATUS "PSReadFile: " ${PSReadFile})
endif()

if(PiPlateUsed)
    find_path(PPBBCMAP NAMES map_BagPiPlateBoardChannel.txt
						HINTS "${PIPLATESECTOR_SOURCE_DIR}" "${PIPLATESECTOR_SOURCE_DIR}/macro")
    set(PPBagBoardChannelMap "${PPBBCMAP}/map_BagPiPlateBoardChannel.txt")
    message(STATUS "PPBagBoardChannelMap: " ${PPBagBoardChannelMap})
endif()


find_path(ASIO_SOURCE_DIR NAMES	asio-1.10.6			PATHS
													${CMAKE_SOURCE_DIR}
													${CMAKE_SOURCE_DIR}/asio
                                                    NO_DEFAULT_PATH)
if(ASIO_SOURCE_DIR)
	set(ASIO_INCLUDE_DIR ${ASIO_SOURCE_DIR}/asio-1.10.6/include)
else(ASIO_SOURCE_DIR)
	message(STATUS "Could NOT find ASIO!\n")
	#add one to report and even quit when the asio is not found
endif()

include_directories(${ASIO_INCLUDE_DIR})
include_directories(include)


CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake ${CMAKE_SOURCE_DIR}/include/config.h)

#add_subdirectory(Basic)
add_subdirectory(Base)

#PiPlateSector will add RelayControl only part
if(PiPlateUsed)
	add_subdirectory(RelayBase)
	add_subdirectory(PiPlateSector)
endif()

#PressureSector will add Pressure senesor measurement only part
if(PressSensorUsed)
	add_subdirectory(PressureSensorBase)
	add_subdirectory(PressureSensorSector)
	add_subdirectory(CentrolControlSector)
endif()

#add_subdirectory(CentrolControlSector)


