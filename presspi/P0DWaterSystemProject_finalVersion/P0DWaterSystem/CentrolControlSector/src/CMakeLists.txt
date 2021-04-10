add_executable(FillCentral FillCentral.cxx)
target_link_libraries(FillCentral ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread) 

add_executable(MonitorCentral MonitorCentral.cxx)
target_link_libraries(MonitorCentral ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread) 


add_executable(DrainCentral DrainCentral.cxx)
target_link_libraries(DrainCentral ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread) 


add_executable(writeDepth writeDepth.cxx)
target_link_libraries(writeDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

add_executable(AllBagDepth AllBagDepth.cxx)
target_link_libraries(AllBagDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)

add_executable(OneTurnFill OneTurnFill.cxx)
target_link_libraries(OneTurnFill ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

add_executable(OneTurnDrain OneTurnDrain.cxx)
target_link_libraries(OneTurnDrain ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

add_executable(FillOneBag FillOneBag.cxx)
target_link_libraries(FillOneBag ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 
