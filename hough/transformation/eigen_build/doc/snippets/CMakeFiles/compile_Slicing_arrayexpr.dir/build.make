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
include doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/flags.make

doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o: doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/flags.make
doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o: doc/snippets/compile_Slicing_arrayexpr.cpp
doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/doc/snippets/Slicing_arrayexpr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_arrayexpr.cpp

doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_arrayexpr.cpp > CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.i

doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_arrayexpr.cpp -o CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.s

# Object files for target compile_Slicing_arrayexpr
compile_Slicing_arrayexpr_OBJECTS = \
"CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o"

# External object files for target compile_Slicing_arrayexpr
compile_Slicing_arrayexpr_EXTERNAL_OBJECTS =

doc/snippets/compile_Slicing_arrayexpr: doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/compile_Slicing_arrayexpr.cpp.o
doc/snippets/compile_Slicing_arrayexpr: doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/build.make
doc/snippets/compile_Slicing_arrayexpr: doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_Slicing_arrayexpr"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_Slicing_arrayexpr.dir/link.txt --verbose=$(VERBOSE)
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && ./compile_Slicing_arrayexpr >/home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/Slicing_arrayexpr.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/build: doc/snippets/compile_Slicing_arrayexpr

.PHONY : doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/build

doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_Slicing_arrayexpr.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/clean

doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/doc/snippets /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_Slicing_arrayexpr.dir/depend
