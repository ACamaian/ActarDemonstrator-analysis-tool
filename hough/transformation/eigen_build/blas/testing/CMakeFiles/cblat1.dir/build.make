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
include blas/testing/CMakeFiles/cblat1.dir/depend.make

# Include the progress variables for this target.
include blas/testing/CMakeFiles/cblat1.dir/progress.make

# Include the compile flags for this target's objects.
include blas/testing/CMakeFiles/cblat1.dir/flags.make

blas/testing/CMakeFiles/cblat1.dir/cblat1.f.o: blas/testing/CMakeFiles/cblat1.dir/flags.make
blas/testing/CMakeFiles/cblat1.dir/cblat1.f.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/blas/testing/cblat1.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object blas/testing/CMakeFiles/cblat1.dir/cblat1.f.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing && /usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /home/camaiani/ATS_ne20/hough/transformation/eigen/blas/testing/cblat1.f -o CMakeFiles/cblat1.dir/cblat1.f.o

blas/testing/CMakeFiles/cblat1.dir/cblat1.f.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/cblat1.dir/cblat1.f.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing && /usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/blas/testing/cblat1.f > CMakeFiles/cblat1.dir/cblat1.f.i

blas/testing/CMakeFiles/cblat1.dir/cblat1.f.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/cblat1.dir/cblat1.f.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing && /usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/blas/testing/cblat1.f -o CMakeFiles/cblat1.dir/cblat1.f.s

# Object files for target cblat1
cblat1_OBJECTS = \
"CMakeFiles/cblat1.dir/cblat1.f.o"

# External object files for target cblat1
cblat1_EXTERNAL_OBJECTS =

blas/testing/cblat1: blas/testing/CMakeFiles/cblat1.dir/cblat1.f.o
blas/testing/cblat1: blas/testing/CMakeFiles/cblat1.dir/build.make
blas/testing/cblat1: blas/libeigen_blas.so
blas/testing/cblat1: blas/testing/CMakeFiles/cblat1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking Fortran executable cblat1"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cblat1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
blas/testing/CMakeFiles/cblat1.dir/build: blas/testing/cblat1

.PHONY : blas/testing/CMakeFiles/cblat1.dir/build

blas/testing/CMakeFiles/cblat1.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing && $(CMAKE_COMMAND) -P CMakeFiles/cblat1.dir/cmake_clean.cmake
.PHONY : blas/testing/CMakeFiles/cblat1.dir/clean

blas/testing/CMakeFiles/cblat1.dir/depend:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/blas/testing /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing /home/camaiani/ATS_ne20/hough/transformation/eigen_build/blas/testing/CMakeFiles/cblat1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : blas/testing/CMakeFiles/cblat1.dir/depend

