add_executable(FillPiPlate FillPiPlate.cxx)
target_link_libraries(FillPiPlate ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a
									${CMAKE_BINARY_DIR}/RelayBase/src/libpiplate.a ${BCM2835_LIBRARY}  -pthread)
#target_link_libraries(FillPiPlate /home/pi/P0DWaterSytemProject/build/Base/src/libGlobalBase.a 
# /home/pi/P0DWaterSytemProject/build/RelayBase/src/libpiplate.a ${BCM2835_LIBRARY}  -pthread)

add_executable(loopRelays_test loopRelays_test.cxx)
target_link_libraries(loopRelays_test ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a
									${CMAKE_BINARY_DIR}/RelayBase/src/libpiplate.a ${BCM2835_LIBRARY}  -pthread)



