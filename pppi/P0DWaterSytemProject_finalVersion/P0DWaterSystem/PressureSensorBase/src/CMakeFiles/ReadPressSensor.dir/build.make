# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem

# Include any dependencies generated for this target.
include PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/depend.make

# Include the progress variables for this target.
include PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/progress.make

# Include the compile flags for this target's objects.
include PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/flags.make

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/flags.make
PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o: PressureSensorBase/src/ReadPressureSensors.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o -c /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadPressureSensors.cxx

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.i"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadPressureSensors.cxx > CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.i

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.s"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadPressureSensors.cxx -o CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.s

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.requires:
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.requires

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.provides: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.requires
	$(MAKE) -f PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/build.make PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.provides.build
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.provides

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.provides.build: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o

# Object files for target ReadPressSensor
ReadPressSensor_OBJECTS = \
"CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o"

# External object files for target ReadPressSensor
ReadPressSensor_EXTERNAL_OBJECTS =

PressureSensorBase/src/libReadPressSensor.a: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o
PressureSensorBase/src/libReadPressSensor.a: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/build.make
PressureSensorBase/src/libReadPressSensor.a: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libReadPressSensor.a"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && $(CMAKE_COMMAND) -P CMakeFiles/ReadPressSensor.dir/cmake_clean_target.cmake
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReadPressSensor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/build: PressureSensorBase/src/libReadPressSensor.a
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/build

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/requires: PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/ReadPressureSensors.cxx.o.requires
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/requires

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/clean:
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src && $(CMAKE_COMMAND) -P CMakeFiles/ReadPressSensor.dir/cmake_clean.cmake
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/clean

PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/depend:
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PressureSensorBase/src/CMakeFiles/ReadPressSensor.dir/depend

