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

# Utility rule file for lscg.

# Include the progress variables for this target.
include test/CMakeFiles/lscg.dir/progress.make

lscg: test/CMakeFiles/lscg.dir/build.make

.PHONY : lscg

# Rule to build all files generated by this target.
test/CMakeFiles/lscg.dir/build: lscg

.PHONY : test/CMakeFiles/lscg.dir/build

test/CMakeFiles/lscg.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && $(CMAKE_COMMAND) -P CMakeFiles/lscg.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/lscg.dir/clean

test/CMakeFiles/lscg.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test/CMakeFiles/lscg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/lscg.dir/depend

