set(PACKAGE CentrolControlSector)

include_directories(${BASE_SOURCE_DIR}/include)
include_directories(${PSENSORBASE_SOURCE_DIR}/include)
include_directories(${PSENSORSECTOR_SOURCE_DIR}/include)
include_directories(${PIPLATESECTOR_SOURCE_DIR}/include)
include_directories(include)


add_subdirectory(src)
