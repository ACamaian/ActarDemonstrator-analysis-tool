# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/camaiani/ATS_ne20/hough/transformation/eigen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/camaiani/ATS_ne20/hough/transformation/eigen_build

# Include any dependencies generated for this target.
include test/CMakeFiles/nullary_10.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/nullary_10.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/nullary_10.dir/flags.make

test/CMakeFiles/nullary_10.dir/nullary.cpp.o: test/CMakeFiles/nullary_10.dir/flags.make
test/CMakeFiles/nullary_10.dir/nullary.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/test/nullary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/nullary_10.dir/nullary.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nullary_10.dir/nullary.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/test/nullary.cpp

test/CMakeFiles/nullary_10.dir/nullary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nullary_10.dir/nullary.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/test/nullary.cpp > CMakeFiles/nullary_10.dir/nullary.cpp.i

test/CMakeFiles/nullary_10.dir/nullary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nullary_10.dir/nullary.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/test/nullary.cpp -o CMakeFiles/nullary_10.dir/nullary.cpp.s

# Object files for target nullary_10
nullary_10_OBJECTS = \
"CMakeFiles/nullary_10.dir/nullary.cpp.o"

# External object files for target nullary_10
nullary_10_EXTERNAL_OBJECTS =

test/nullary_10: test/CMakeFiles/nullary_10.dir/nullary.cpp.o
test/nullary_10: test/CMakeFiles/nullary_10.dir/build.make
test/nullary_10: test/CMakeFiles/nullary_10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nullary_10"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nullary_10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/nullary_10.dir/build: test/nullary_10

.PHONY : test/CMakeFiles/nullary_10.dir/build

test/CMakeFiles/nullary_10.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && $(CMAKE_COMMAND) -P CMakeFiles/nullary_10.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/nullary_10.dir/clean

test/CMakeFiles/nullary_10.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test/CMakeFiles/nullary_10.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/nullary_10.dir/depend

