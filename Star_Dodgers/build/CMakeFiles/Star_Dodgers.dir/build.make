# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build

# Include any dependencies generated for this target.
include CMakeFiles/Star_Dodgers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Star_Dodgers.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Star_Dodgers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Star_Dodgers.dir/flags.make

CMakeFiles/Star_Dodgers.dir/Source.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/Source.cpp.o: ../Source.cpp
CMakeFiles/Star_Dodgers.dir/Source.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Star_Dodgers.dir/Source.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/Source.cpp.o -MF CMakeFiles/Star_Dodgers.dir/Source.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/Source.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp

CMakeFiles/Star_Dodgers.dir/Source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/Source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp > CMakeFiles/Star_Dodgers.dir/Source.cpp.i

CMakeFiles/Star_Dodgers.dir/Source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/Source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp -o CMakeFiles/Star_Dodgers.dir/Source.cpp.s

# Object files for target Star_Dodgers
Star_Dodgers_OBJECTS = \
"CMakeFiles/Star_Dodgers.dir/Source.cpp.o"

# External object files for target Star_Dodgers
Star_Dodgers_EXTERNAL_OBJECTS =

Star_Dodgers: CMakeFiles/Star_Dodgers.dir/Source.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/build.make
Star_Dodgers: /usr/lib/libsfml-graphics.so.2.5.1
Star_Dodgers: /usr/lib/libsfml-window.so.2.5.1
Star_Dodgers: /usr/lib/libsfml-system.so.2.5.1
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Star_Dodgers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Star_Dodgers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Star_Dodgers.dir/build: Star_Dodgers
.PHONY : CMakeFiles/Star_Dodgers.dir/build

CMakeFiles/Star_Dodgers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Star_Dodgers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Star_Dodgers.dir/clean

CMakeFiles/Star_Dodgers.dir/depend:
	cd /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/build/CMakeFiles/Star_Dodgers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Star_Dodgers.dir/depend
