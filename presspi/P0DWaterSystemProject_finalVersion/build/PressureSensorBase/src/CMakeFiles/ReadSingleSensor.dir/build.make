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
CMAKE_BINARY_DIR = /home/pi/P0DWaterSystemProject_finalVersion/build

# Include any dependencies generated for this target.
include PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/depend.make

# Include the progress variables for this target.
include PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/progress.make

# Include the compile flags for this target's objects.
include PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/flags.make

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/flags.make
PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o: /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadSingleSensor.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSystemProject_finalVersion/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o -c /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadSingleSensor.cxx

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.i"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadSingleSensor.cxx > CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.i

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.s"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src/ReadSingleSensor.cxx -o CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.s

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.requires:
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.requires

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.provides: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.requires
	$(MAKE) -f PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/build.make PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.provides.build
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.provides

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.provides.build: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o

# Object files for target ReadSingleSensor
ReadSingleSensor_OBJECTS = \
"CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o"

# External object files for target ReadSingleSensor
ReadSingleSensor_EXTERNAL_OBJECTS =

PressureSensorBase/src/ReadSingleSensor: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o
PressureSensorBase/src/ReadSingleSensor: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/build.make
PressureSensorBase/src/ReadSingleSensor: PressureSensorBase/src/libReadPressSensor.a
PressureSensorBase/src/ReadSingleSensor: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ReadSingleSensor"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReadSingleSensor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/build: PressureSensorBase/src/ReadSingleSensor
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/build

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/requires: PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/ReadSingleSensor.cxx.o.requires
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/requires

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/clean:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src && $(CMAKE_COMMAND) -P CMakeFiles/ReadSingleSensor.dir/cmake_clean.cmake
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/clean

PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/depend:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/PressureSensorBase/src /home/pi/P0DWaterSystemProject_finalVersion/build /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src /home/pi/P0DWaterSystemProject_finalVersion/build/PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PressureSensorBase/src/CMakeFiles/ReadSingleSensor.dir/depend

