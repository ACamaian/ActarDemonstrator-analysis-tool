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
include doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/flags.make

doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o: doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/flags.make
doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o: doc/snippets/compile_Slicing_custom_padding_cxx11.cpp
doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/doc/snippets/Slicing_custom_padding_cxx11.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_custom_padding_cxx11.cpp

doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_custom_padding_cxx11.cpp > CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.i

doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/compile_Slicing_custom_padding_cxx11.cpp -o CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.s

# Object files for target compile_Slicing_custom_padding_cxx11
compile_Slicing_custom_padding_cxx11_OBJECTS = \
"CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o"

# External object files for target compile_Slicing_custom_padding_cxx11
compile_Slicing_custom_padding_cxx11_EXTERNAL_OBJECTS =

doc/snippets/compile_Slicing_custom_padding_cxx11: doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/compile_Slicing_custom_padding_cxx11.cpp.o
doc/snippets/compile_Slicing_custom_padding_cxx11: doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/build.make
doc/snippets/compile_Slicing_custom_padding_cxx11: doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_Slicing_custom_padding_cxx11"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/link.txt --verbose=$(VERBOSE)
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && ./compile_Slicing_custom_padding_cxx11 >/home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/Slicing_custom_padding_cxx11.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/build: doc/snippets/compile_Slicing_custom_padding_cxx11

.PHONY : doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/build

doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/clean

doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/doc/snippets /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets /home/camaiani/ATS_ne20/hough/transformation/eigen_build/doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_Slicing_custom_padding_cxx11.dir/depend

