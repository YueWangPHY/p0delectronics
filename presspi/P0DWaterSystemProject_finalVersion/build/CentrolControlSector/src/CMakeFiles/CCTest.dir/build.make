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
include CentrolControlSector/src/CMakeFiles/CCTest.dir/depend.make

# Include the progress variables for this target.
include CentrolControlSector/src/CMakeFiles/CCTest.dir/progress.make

# Include the compile flags for this target's objects.
include CentrolControlSector/src/CMakeFiles/CCTest.dir/flags.make

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o: CentrolControlSector/src/CMakeFiles/CCTest.dir/flags.make
CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o: /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/CCTest.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSystemProject_finalVersion/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CCTest.dir/CCTest.cxx.o -c /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/CCTest.cxx

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CCTest.dir/CCTest.cxx.i"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/CCTest.cxx > CMakeFiles/CCTest.dir/CCTest.cxx.i

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CCTest.dir/CCTest.cxx.s"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src/CCTest.cxx -o CMakeFiles/CCTest.dir/CCTest.cxx.s

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.requires:
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.requires

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.provides: CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.requires
	$(MAKE) -f CentrolControlSector/src/CMakeFiles/CCTest.dir/build.make CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.provides.build
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.provides

CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.provides.build: CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o

# Object files for target CCTest
CCTest_OBJECTS = \
"CMakeFiles/CCTest.dir/CCTest.cxx.o"

# External object files for target CCTest
CCTest_EXTERNAL_OBJECTS =

CentrolControlSector/src/CCTest: CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o
CentrolControlSector/src/CCTest: CentrolControlSector/src/CMakeFiles/CCTest.dir/build.make
CentrolControlSector/src/CCTest: CentrolControlSector/src/CMakeFiles/CCTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable CCTest"
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CCTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CentrolControlSector/src/CMakeFiles/CCTest.dir/build: CentrolControlSector/src/CCTest
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/build

CentrolControlSector/src/CMakeFiles/CCTest.dir/requires: CentrolControlSector/src/CMakeFiles/CCTest.dir/CCTest.cxx.o.requires
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/requires

CentrolControlSector/src/CMakeFiles/CCTest.dir/clean:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src && $(CMAKE_COMMAND) -P CMakeFiles/CCTest.dir/cmake_clean.cmake
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/clean

CentrolControlSector/src/CMakeFiles/CCTest.dir/depend:
	cd /home/pi/P0DWaterSystemProject_finalVersion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CentrolControlSector/src /home/pi/P0DWaterSystemProject_finalVersion/build /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src /home/pi/P0DWaterSystemProject_finalVersion/build/CentrolControlSector/src/CMakeFiles/CCTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CentrolControlSector/src/CMakeFiles/CCTest.dir/depend

