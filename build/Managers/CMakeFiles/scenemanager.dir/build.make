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
include Managers/CMakeFiles/scenemanager.dir/depend.make

# Include the progress variables for this target.
include Managers/CMakeFiles/scenemanager.dir/progress.make

# Include the compile flags for this target's objects.
include Managers/CMakeFiles/scenemanager.dir/flags.make

Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.o: Managers/CMakeFiles/scenemanager.dir/flags.make
Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.o: ../Managers/SceneManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.o"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scenemanager.dir/SceneManager.cpp.o -c /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Managers/SceneManager.cpp

Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scenemanager.dir/SceneManager.cpp.i"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Managers/SceneManager.cpp > CMakeFiles/scenemanager.dir/SceneManager.cpp.i

Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scenemanager.dir/SceneManager.cpp.s"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Managers/SceneManager.cpp -o CMakeFiles/scenemanager.dir/SceneManager.cpp.s

# Object files for target scenemanager
scenemanager_OBJECTS = \
"CMakeFiles/scenemanager.dir/SceneManager.cpp.o"

# External object files for target scenemanager
scenemanager_EXTERNAL_OBJECTS =

Managers/libscenemanager.a: Managers/CMakeFiles/scenemanager.dir/SceneManager.cpp.o
Managers/libscenemanager.a: Managers/CMakeFiles/scenemanager.dir/build.make
Managers/libscenemanager.a: Managers/CMakeFiles/scenemanager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libscenemanager.a"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && $(CMAKE_COMMAND) -P CMakeFiles/scenemanager.dir/cmake_clean_target.cmake
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scenemanager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Managers/CMakeFiles/scenemanager.dir/build: Managers/libscenemanager.a

.PHONY : Managers/CMakeFiles/scenemanager.dir/build

Managers/CMakeFiles/scenemanager.dir/clean:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers && $(CMAKE_COMMAND) -P CMakeFiles/scenemanager.dir/cmake_clean.cmake
.PHONY : Managers/CMakeFiles/scenemanager.dir/clean

Managers/CMakeFiles/scenemanager.dir/depend:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jordan/Desktop/ProgrammingStuff/opengltest/test1 /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Managers /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Managers/CMakeFiles/scenemanager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Managers/CMakeFiles/scenemanager.dir/depend

