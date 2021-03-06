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
include CentrolControlSector/src/CMakeFiles/ReadDepth.dir/depend.make

# Include the progress variables for this target.
include CentrolControlSector/src/CMakeFiles/ReadDepth.dir/progress.make

# Include the compile flags for this target's objects.
include CentrolControlSector/src/CMakeFiles/ReadDepth.dir/flags.make

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/flags.make
CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o: /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/ReadDepth.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSystemProject_finalVersion/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o -c /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/ReadDepth.cxx

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ReadDepth.dir/ReadDepth.cxx.i"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/ReadDepth.cxx > CMakeFiles/ReadDepth.dir/ReadDepth.cxx.i

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ReadDepth.dir/ReadDepth.cxx.s"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/ReadDepth.cxx -o CMakeFiles/ReadDepth.dir/ReadDepth.cxx.s

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.requires:
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.requires

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.provides: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.requires
	$(MAKE) -f CentrolControlSector/src/CMakeFiles/ReadDepth.dir/build.make CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.provides.build
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.provides

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.provides.build: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o

# Object files for target ReadDepth
ReadDepth_OBJECTS = \
"CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o"

# External object files for target ReadDepth
ReadDepth_EXTERNAL_OBJECTS =

CentrolControlSector/src/ReadDepth: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o
CentrolControlSector/src/ReadDepth: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/build.make
CentrolControlSector/src/ReadDepth: Base/src/libGlobalBase.a
CentrolControlSector/src/ReadDepth: PressureSensorBase/src/libReadPressSensor.a
CentrolControlSector/src/ReadDepth: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ReadDepth"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReadDepth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CentrolControlSector/src/CMakeFiles/ReadDepth.dir/build: CentrolControlSector/src/ReadDepth
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/build

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/requires: CentrolControlSector/src/CMakeFiles/ReadDepth.dir/ReadDepth.cxx.o.requires
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/requires

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/clean:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && $(CMAKE_COMMAND) -P CMakeFiles/ReadDepth.dir/cmake_clean.cmake
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/clean

CentrolControlSector/src/CMakeFiles/ReadDepth.dir/depend:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src /home/pi/P0DWaterSystemProject_finalVersion/build /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src/CMakeFiles/ReadDepth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CentrolControlSector/src/CMakeFiles/ReadDepth.dir/depend

