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
CMAKE_SOURCE_DIR = /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/P0DWaterSytemProject_finalVersion/build

# Include any dependencies generated for this target.
include Base/src/CMakeFiles/testBase.dir/depend.make

# Include the progress variables for this target.
include Base/src/CMakeFiles/testBase.dir/progress.make

# Include the compile flags for this target's objects.
include Base/src/CMakeFiles/testBase.dir/flags.make

Base/src/CMakeFiles/testBase.dir/test.cxx.o: Base/src/CMakeFiles/testBase.dir/flags.make
Base/src/CMakeFiles/testBase.dir/test.cxx.o: /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/Base/src/test.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/P0DWaterSytemProject_finalVersion/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Base/src/CMakeFiles/testBase.dir/test.cxx.o"
	cd /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testBase.dir/test.cxx.o -c /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/Base/src/test.cxx

Base/src/CMakeFiles/testBase.dir/test.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testBase.dir/test.cxx.i"
	cd /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/Base/src/test.cxx > CMakeFiles/testBase.dir/test.cxx.i

Base/src/CMakeFiles/testBase.dir/test.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testBase.dir/test.cxx.s"
	cd /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/Base/src/test.cxx -o CMakeFiles/testBase.dir/test.cxx.s

Base/src/CMakeFiles/testBase.dir/test.cxx.o.requires:
.PHONY : Base/src/CMakeFiles/testBase.dir/test.cxx.o.requires

Base/src/CMakeFiles/testBase.dir/test.cxx.o.provides: Base/src/CMakeFiles/testBase.dir/test.cxx.o.requires
	$(MAKE) -f Base/src/CMakeFiles/testBase.dir/build.make Base/src/CMakeFiles/testBase.dir/test.cxx.o.provides.build
.PHONY : Base/src/CMakeFiles/testBase.dir/test.cxx.o.provides

Base/src/CMakeFiles/testBase.dir/test.cxx.o.provides.build: Base/src/CMakeFiles/testBase.dir/test.cxx.o

# Object files for target testBase
testBase_OBJECTS = \
"CMakeFiles/testBase.dir/test.cxx.o"

# External object files for target testBase
testBase_EXTERNAL_OBJECTS =

Base/src/testBase: Base/src/CMakeFiles/testBase.dir/test.cxx.o
Base/src/testBase: Base/src/CMakeFiles/testBase.dir/build.make
Base/src/testBase: Base/src/libGlobalBase.a
Base/src/testBase: Base/src/CMakeFiles/testBase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable testBase"
	cd /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testBase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Base/src/CMakeFiles/testBase.dir/build: Base/src/testBase
.PHONY : Base/src/CMakeFiles/testBase.dir/build

Base/src/CMakeFiles/testBase.dir/requires: Base/src/CMakeFiles/testBase.dir/test.cxx.o.requires
.PHONY : Base/src/CMakeFiles/testBase.dir/requires

Base/src/CMakeFiles/testBase.dir/clean:
	cd /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src && $(CMAKE_COMMAND) -P CMakeFiles/testBase.dir/cmake_clean.cmake
.PHONY : Base/src/CMakeFiles/testBase.dir/clean

Base/src/CMakeFiles/testBase.dir/depend:
	cd /home/pi/P0DWaterSytemProject_finalVersion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem /home/pi/P0DWaterSytemProject_finalVersion/P0DWaterSystem/Base/src /home/pi/P0DWaterSytemProject_finalVersion/build /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src /home/pi/P0DWaterSytemProject_finalVersion/build/Base/src/CMakeFiles/testBase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Base/src/CMakeFiles/testBase.dir/depend

