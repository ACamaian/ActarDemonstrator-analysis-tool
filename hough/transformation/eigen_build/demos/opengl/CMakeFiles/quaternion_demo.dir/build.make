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
include demos/opengl/CMakeFiles/quaternion_demo.dir/depend.make

# Include the progress variables for this target.
include demos/opengl/CMakeFiles/quaternion_demo.dir/progress.make

# Include the compile flags for this target's objects.
include demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make

demos/opengl/quaternion_demo.moc: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/quaternion_demo.h
demos/opengl/quaternion_demo.moc: demos/opengl/quaternion_demo.moc_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating quaternion_demo.moc"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl/quaternion_demo.moc_parameters

demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o: demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make
demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/gpuhelper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/gpuhelper.cpp

demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/gpuhelper.cpp > CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.i

demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/gpuhelper.cpp -o CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.s

demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.o: demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make
demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/icosphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quaternion_demo.dir/icosphere.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/icosphere.cpp

demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quaternion_demo.dir/icosphere.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/icosphere.cpp > CMakeFiles/quaternion_demo.dir/icosphere.cpp.i

demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quaternion_demo.dir/icosphere.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/icosphere.cpp -o CMakeFiles/quaternion_demo.dir/icosphere.cpp.s

demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.o: demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make
demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quaternion_demo.dir/camera.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/camera.cpp

demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quaternion_demo.dir/camera.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/camera.cpp > CMakeFiles/quaternion_demo.dir/camera.cpp.i

demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quaternion_demo.dir/camera.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/camera.cpp -o CMakeFiles/quaternion_demo.dir/camera.cpp.s

demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.o: demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make
demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/trackball.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quaternion_demo.dir/trackball.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/trackball.cpp

demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quaternion_demo.dir/trackball.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/trackball.cpp > CMakeFiles/quaternion_demo.dir/trackball.cpp.i

demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quaternion_demo.dir/trackball.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/trackball.cpp -o CMakeFiles/quaternion_demo.dir/trackball.cpp.s

demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o: demos/opengl/CMakeFiles/quaternion_demo.dir/flags.make
demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o: /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/quaternion_demo.cpp
demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o: demos/opengl/quaternion_demo.moc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o -c /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/quaternion_demo.cpp

demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.i"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/quaternion_demo.cpp > CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.i

demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.s"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl/quaternion_demo.cpp -o CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.s

# Object files for target quaternion_demo
quaternion_demo_OBJECTS = \
"CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o" \
"CMakeFiles/quaternion_demo.dir/icosphere.cpp.o" \
"CMakeFiles/quaternion_demo.dir/camera.cpp.o" \
"CMakeFiles/quaternion_demo.dir/trackball.cpp.o" \
"CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o"

# External object files for target quaternion_demo
quaternion_demo_EXTERNAL_OBJECTS =

demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/gpuhelper.cpp.o
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/icosphere.cpp.o
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/camera.cpp.o
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/trackball.cpp.o
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/quaternion_demo.cpp.o
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/build.make
demos/opengl/quaternion_demo: /usr/lib/x86_64-linux-gnu/libQtCore.so
demos/opengl/quaternion_demo: /usr/lib/x86_64-linux-gnu/libQtGui.so
demos/opengl/quaternion_demo: /usr/lib/x86_64-linux-gnu/libQtOpenGL.so
demos/opengl/quaternion_demo: /usr/lib/x86_64-linux-gnu/libGL.so
demos/opengl/quaternion_demo: /usr/lib/x86_64-linux-gnu/libGLU.so
demos/opengl/quaternion_demo: demos/opengl/CMakeFiles/quaternion_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camaiani/ATS_ne20/hough/transformation/eigen_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable quaternion_demo"
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quaternion_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demos/opengl/CMakeFiles/quaternion_demo.dir/build: demos/opengl/quaternion_demo

.PHONY : demos/opengl/CMakeFiles/quaternion_demo.dir/build

demos/opengl/CMakeFiles/quaternion_demo.dir/clean:
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl && $(CMAKE_COMMAND) -P CMakeFiles/quaternion_demo.dir/cmake_clean.cmake
.PHONY : demos/opengl/CMakeFiles/quaternion_demo.dir/clean

demos/opengl/CMakeFiles/quaternion_demo.dir/depend: demos/opengl/quaternion_demo.moc
	cd /home/camaiani/ATS_ne20/hough/transformation/eigen_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camaiani/ATS_ne20/hough/transformation/eigen /home/camaiani/ATS_ne20/hough/transformation/eigen/demos/opengl /home/camaiani/ATS_ne20/hough/transformation/eigen_build /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl /home/camaiani/ATS_ne20/hough/transformation/eigen_build/demos/opengl/CMakeFiles/quaternion_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demos/opengl/CMakeFiles/quaternion_demo.dir/depend

