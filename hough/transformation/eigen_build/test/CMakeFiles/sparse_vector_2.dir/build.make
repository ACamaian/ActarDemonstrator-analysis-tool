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
include test/CMakeFiles/sparse_vector_2.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/sparse_vector_2.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/sparse_vector_2.dir/flags.make

test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o: test/CMakeFiles/sparse_vector_2.dir/flags.make
test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/test/sparse_vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/test/sparse_vector.cpp

test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/test/sparse_vector.cpp > CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.i

test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/test/sparse_vector.cpp -o CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.s

# Object files for target sparse_vector_2
sparse_vector_2_OBJECTS = \
"CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o"

# External object files for target sparse_vector_2
sparse_vector_2_EXTERNAL_OBJECTS =

test/sparse_vector_2: test/CMakeFiles/sparse_vector_2.dir/sparse_vector.cpp.o
test/sparse_vector_2: test/CMakeFiles/sparse_vector_2.dir/build.make
test/sparse_vector_2: test/CMakeFiles/sparse_vector_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sparse_vector_2"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sparse_vector_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/sparse_vector_2.dir/build: test/sparse_vector_2

.PHONY : test/CMakeFiles/sparse_vector_2.dir/build

test/CMakeFiles/sparse_vector_2.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test && $(CMAKE_COMMAND) -P CMakeFiles/sparse_vector_2.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/sparse_vector_2.dir/clean

test/CMakeFiles/sparse_vector_2.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test /home/camaiani/ATS_ne20/hough/transformation/eigen_build/test/CMakeFiles/sparse_vector_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/sparse_vector_2.dir/depend

