# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Users\mds000020d\scoop\apps\cmake\3.21.1\bin\cmake.exe

# The command to remove a file.
RM = D:\Users\mds000020d\scoop\apps\cmake\3.21.1\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers\build

# Utility rule file for NightlyMemCheck.

# Include any custom commands dependencies for this target.
include CMakeFiles/NightlyMemCheck.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NightlyMemCheck.dir/progress.make

CMakeFiles/NightlyMemCheck:
	D:\Users\mds000020d\scoop\apps\cmake\3.21.1\bin\ctest.exe -D NightlyMemCheck

NightlyMemCheck: CMakeFiles/NightlyMemCheck
NightlyMemCheck: CMakeFiles/NightlyMemCheck.dir/build.make
.PHONY : NightlyMemCheck

# Rule to build all files generated by this target.
CMakeFiles/NightlyMemCheck.dir/build: NightlyMemCheck
.PHONY : CMakeFiles/NightlyMemCheck.dir/build

CMakeFiles/NightlyMemCheck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NightlyMemCheck.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NightlyMemCheck.dir/clean

CMakeFiles/NightlyMemCheck.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers\build D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers\build D:\Users\mds000020d\Documents\Repos\Star_Dodgers\Star_Dodgers\build\CMakeFiles\NightlyMemCheck.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NightlyMemCheck.dir/depend

