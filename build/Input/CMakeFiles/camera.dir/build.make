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
CMAKE_SOURCE_DIR = /home/jordan/Desktop/ProgrammingStuff/opengltest/test1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build

# Include any dependencies generated for this target.
include Input/CMakeFiles/camera.dir/depend.make

# Include the progress variables for this target.
include Input/CMakeFiles/camera.dir/progress.make

# Include the compile flags for this target's objects.
include Input/CMakeFiles/camera.dir/flags.make

Input/CMakeFiles/camera.dir/Camera.cpp.o: Input/CMakeFiles/camera.dir/flags.make
Input/CMakeFiles/camera.dir/Camera.cpp.o: ../Input/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Input/CMakeFiles/camera.dir/Camera.cpp.o"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/camera.dir/Camera.cpp.o -c /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Input/Camera.cpp

Input/CMakeFiles/camera.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera.dir/Camera.cpp.i"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Input/Camera.cpp > CMakeFiles/camera.dir/Camera.cpp.i

Input/CMakeFiles/camera.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera.dir/Camera.cpp.s"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Input/Camera.cpp -o CMakeFiles/camera.dir/Camera.cpp.s

# Object files for target camera
camera_OBJECTS = \
"CMakeFiles/camera.dir/Camera.cpp.o"

# External object files for target camera
camera_EXTERNAL_OBJECTS =

Input/libcamera.a: Input/CMakeFiles/camera.dir/Camera.cpp.o
Input/libcamera.a: Input/CMakeFiles/camera.dir/build.make
Input/libcamera.a: Input/CMakeFiles/camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcamera.a"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && $(CMAKE_COMMAND) -P CMakeFiles/camera.dir/cmake_clean_target.cmake
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Input/CMakeFiles/camera.dir/build: Input/libcamera.a

.PHONY : Input/CMakeFiles/camera.dir/build

Input/CMakeFiles/camera.dir/clean:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input && $(CMAKE_COMMAND) -P CMakeFiles/camera.dir/cmake_clean.cmake
.PHONY : Input/CMakeFiles/camera.dir/clean

Input/CMakeFiles/camera.dir/depend:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jordan/Desktop/ProgrammingStuff/opengltest/test1 /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Input /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Input/CMakeFiles/camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Input/CMakeFiles/camera.dir/depend

