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
include RelayBase/src/CMakeFiles/InitPiPlate.dir/depend.make

# Include the progress variables for this target.
include RelayBase/src/CMakeFiles/InitPiPlate.dir/progress.make

# Include the compile flags for this target's objects.
include RelayBase/src/CMakeFiles/InitPiPlate.dir/flags.make

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o: RelayBase/src/CMakeFiles/InitPiPlate.dir/flags.make
RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o: RelayBase/src/InitPiPlate.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o -c /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src/InitPiPlate.cxx

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.i"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src/InitPiPlate.cxx > CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.i

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.s"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src/InitPiPlate.cxx -o CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.s

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.requires:
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.requires

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.provides: RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.requires
	$(MAKE) -f RelayBase/src/CMakeFiles/InitPiPlate.dir/build.make RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.provides.build
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.provides

RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.provides.build: RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o

# Object files for target InitPiPlate
InitPiPlate_OBJECTS = \
"CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o"

# External object files for target InitPiPlate
InitPiPlate_EXTERNAL_OBJECTS =

RelayBase/src/InitPiPlate: RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o
RelayBase/src/InitPiPlate: RelayBase/src/CMakeFiles/InitPiPlate.dir/build.make
RelayBase/src/InitPiPlate: RelayBase/src/libpiplate.a
RelayBase/src/InitPiPlate: RelayBase/lib/libbcm2835.a
RelayBase/src/InitPiPlate: RelayBase/src/CMakeFiles/InitPiPlate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable InitPiPlate"
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/InitPiPlate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
RelayBase/src/CMakeFiles/InitPiPlate.dir/build: RelayBase/src/InitPiPlate
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/build

RelayBase/src/CMakeFiles/InitPiPlate.dir/requires: RelayBase/src/CMakeFiles/InitPiPlate.dir/InitPiPlate.cxx.o.requires
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/requires

RelayBase/src/CMakeFiles/InitPiPlate.dir/clean:
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src && $(CMAKE_COMMAND) -P CMakeFiles/InitPiPlate.dir/cmake_clean.cmake
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/clean

RelayBase/src/CMakeFiles/InitPiPlate.dir/depend:
	cd /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src /home/pi/P0DWaterSystemProject_finalVersion/P0DWaterSystem/RelayBase/src/CMakeFiles/InitPiPlate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : RelayBase/src/CMakeFiles/InitPiPlate.dir/depend

