set(PACKAGE RelayBase)

find_library(BCM2835_LIBRARY NAMES bcm2835
											HINTS "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*" "${PROJECT_SOURCE_DIR}/*/*")
			     
message("LIBRARY: " ${BCM2835_LIBRARY})

include_directories(include)

add_subdirectory(src)

		   
