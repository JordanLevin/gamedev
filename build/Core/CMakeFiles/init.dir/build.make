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
include Core/CMakeFiles/init.dir/depend.make

# Include the progress variables for this target.
include Core/CMakeFiles/init.dir/progress.make

# Include the compile flags for this target's objects.
include Core/CMakeFiles/init.dir/flags.make

Core/CMakeFiles/init.dir/Init/InitGlew.cpp.o: Core/CMakeFiles/init.dir/flags.make
Core/CMakeFiles/init.dir/Init/InitGlew.cpp.o: ../Core/Init/InitGlew.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Core/CMakeFiles/init.dir/Init/InitGlew.cpp.o"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/init.dir/Init/InitGlew.cpp.o -c /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlew.cpp

Core/CMakeFiles/init.dir/Init/InitGlew.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/init.dir/Init/InitGlew.cpp.i"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlew.cpp > CMakeFiles/init.dir/Init/InitGlew.cpp.i

Core/CMakeFiles/init.dir/Init/InitGlew.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/init.dir/Init/InitGlew.cpp.s"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlew.cpp -o CMakeFiles/init.dir/Init/InitGlew.cpp.s

Core/CMakeFiles/init.dir/Init/InitGlut.cpp.o: Core/CMakeFiles/init.dir/flags.make
Core/CMakeFiles/init.dir/Init/InitGlut.cpp.o: ../Core/Init/InitGlut.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Core/CMakeFiles/init.dir/Init/InitGlut.cpp.o"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/init.dir/Init/InitGlut.cpp.o -c /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlut.cpp

Core/CMakeFiles/init.dir/Init/InitGlut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/init.dir/Init/InitGlut.cpp.i"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlut.cpp > CMakeFiles/init.dir/Init/InitGlut.cpp.i

Core/CMakeFiles/init.dir/Init/InitGlut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/init.dir/Init/InitGlut.cpp.s"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core/Init/InitGlut.cpp -o CMakeFiles/init.dir/Init/InitGlut.cpp.s

# Object files for target init
init_OBJECTS = \
"CMakeFiles/init.dir/Init/InitGlew.cpp.o" \
"CMakeFiles/init.dir/Init/InitGlut.cpp.o"

# External object files for target init
init_EXTERNAL_OBJECTS =

Core/libinit.a: Core/CMakeFiles/init.dir/Init/InitGlew.cpp.o
Core/libinit.a: Core/CMakeFiles/init.dir/Init/InitGlut.cpp.o
Core/libinit.a: Core/CMakeFiles/init.dir/build.make
Core/libinit.a: Core/CMakeFiles/init.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libinit.a"
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && $(CMAKE_COMMAND) -P CMakeFiles/init.dir/cmake_clean_target.cmake
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/init.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Core/CMakeFiles/init.dir/build: Core/libinit.a

.PHONY : Core/CMakeFiles/init.dir/build

Core/CMakeFiles/init.dir/clean:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core && $(CMAKE_COMMAND) -P CMakeFiles/init.dir/cmake_clean.cmake
.PHONY : Core/CMakeFiles/init.dir/clean

Core/CMakeFiles/init.dir/depend:
	cd /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jordan/Desktop/ProgrammingStuff/opengltest/test1 /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/Core /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core /home/jordan/Desktop/ProgrammingStuff/opengltest/test1/build/Core/CMakeFiles/init.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Core/CMakeFiles/init.dir/depend

