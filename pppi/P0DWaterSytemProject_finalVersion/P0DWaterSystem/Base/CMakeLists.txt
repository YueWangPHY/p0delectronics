set(PACKAGE Base)

#later add FInd_package to find the include below so that even the .h file is installed in other folders, the can also be found and used
include_directories(include)
add_subdirectory(src)
#add_subdirectory(macro)
