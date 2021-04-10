add_library(GlobalBase GlobalBase.cxx)

add_executable(testBase test.cxx)
target_link_libraries(testBase GlobalBase)


