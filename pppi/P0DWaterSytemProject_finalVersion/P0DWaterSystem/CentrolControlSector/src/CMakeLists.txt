#add_library(MeasureAllDepth MeasureAllDepth.cxx)
#target_link_libraries(MeasureAllDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 


add_executable(CCTest CCTest.cxx)
target_link_libraries(CCTest -pthread) 

add_executable(Central Central.cxx)
#to make the package more portable, can add a FindLib here or in Base CMakeLists, define the path of where the lib will be and then use that path here. 
target_link_libraries(Central ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

add_executable(FillCentral FillCentral.cxx)
target_link_libraries(FillCentral ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread) 

add_executable(DrainCentral DrainCentral.cxx)
target_link_libraries(DrainCentral ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 


add_executable(writeDepth writeDepth.cxx)
target_link_libraries(writeDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

add_executable(AllBagDepth AllBagDepth.cxx)
target_link_libraries(AllBagDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)


add_executable(ReadDepth ReadDepth.cxx)
target_link_libraries(ReadDepth ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)

add_executable(OneTurnFill OneTurnFill.cxx)
target_link_libraries(OneTurnFill ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a -pthread) 

