add_library(piplate piplate.c)
target_link_libraries(piplate ${BCM2835_LIBRARY})


add_executable(relayOn relayOn.cxx)
add_compile_options(-g -O0 -std=c++11 -pthread)
target_link_libraries(relayOn piplate ${BCM2835_LIBRARY})

add_executable(relayOff relayOff.cxx)
add_compile_options(-g -O0 -std=c++11 -pthread)
target_link_libraries(relayOff piplate ${BCM2835_LIBRARY})

add_executable(InitPiPlate InitPiPlate.cxx)
add_compile_options(-g -O0 -std=c++11 -pthread)
target_link_libraries(InitPiPlate piplate ${BCM2835_LIBRARY})

message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})


#install(TARGETS relayOn DESTINATION bin)
#install(TARGETS relayOff DESTINATION bin)

#install(TARGETS piplate DESTINATION lib)


