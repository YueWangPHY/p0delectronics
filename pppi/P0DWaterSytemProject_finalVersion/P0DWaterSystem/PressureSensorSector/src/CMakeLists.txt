add_executable(PSTest PSTest.cxx)
target_link_libraries(PSTest ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a 
							${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)

add_executable(ReadSingleBag ReadSingleBag.cxx)
add_executable(ReadAllBags ReadAllBags.cxx)

target_link_libraries(ReadSingleBag ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)
target_link_libraries(ReadAllBags ${CMAKE_BINARY_DIR}/Base/src/libGlobalBase.a ${CMAKE_BINARY_DIR}/PressureSensorBase/src/libReadPressSensor.a -pthread)



