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
CMAKE_BINARY_DIR = /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers

# Include any dependencies generated for this target.
include CMakeFiles/Star_Dodgers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Star_Dodgers.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Star_Dodgers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Star_Dodgers.dir/flags.make

CMakeFiles/Star_Dodgers.dir/CBall.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CBall.cpp.o: CBall.cpp
CMakeFiles/Star_Dodgers.dir/CBall.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Star_Dodgers.dir/CBall.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CBall.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CBall.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CBall.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CBall.cpp

CMakeFiles/Star_Dodgers.dir/CBall.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CBall.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CBall.cpp > CMakeFiles/Star_Dodgers.dir/CBall.cpp.i

CMakeFiles/Star_Dodgers.dir/CBall.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CBall.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CBall.cpp -o CMakeFiles/Star_Dodgers.dir/CBall.cpp.s

CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o: CControlsMenu.cpp
CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CControlsMenu.cpp

CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CControlsMenu.cpp > CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.i

CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CControlsMenu.cpp -o CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.s

CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o: CGameManager.cpp
CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameManager.cpp

CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameManager.cpp > CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.i

CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameManager.cpp -o CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.s

CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o: CGameScene.cpp
CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameScene.cpp

CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameScene.cpp > CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.i

CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGameScene.cpp -o CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.s

CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o: CGamepad.cpp
CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGamepad.cpp

CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGamepad.cpp > CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.i

CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CGamepad.cpp -o CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.s

CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o: CLobby.cpp
CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CLobby.cpp

CMakeFiles/Star_Dodgers.dir/CLobby.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CLobby.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CLobby.cpp > CMakeFiles/Star_Dodgers.dir/CLobby.cpp.i

CMakeFiles/Star_Dodgers.dir/CLobby.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CLobby.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CLobby.cpp -o CMakeFiles/Star_Dodgers.dir/CLobby.cpp.s

CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o: CMainMenu.cpp
CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMainMenu.cpp

CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMainMenu.cpp > CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.i

CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMainMenu.cpp -o CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.s

CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o: CPlayer.cpp
CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CPlayer.cpp

CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CPlayer.cpp > CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.i

CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CPlayer.cpp -o CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.s

CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o: CResourceHolder.cpp
CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CResourceHolder.cpp

CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CResourceHolder.cpp > CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.i

CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CResourceHolder.cpp -o CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.s

CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o: CTeamsManager.cpp
CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CTeamsManager.cpp

CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CTeamsManager.cpp > CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.i

CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CTeamsManager.cpp -o CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.s

CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o: CUIBar.cpp
CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o -MF CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CUIBar.cpp

CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CUIBar.cpp > CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.i

CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CUIBar.cpp -o CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.s

CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o: EasySFML.cpp
CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o -MF CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/EasySFML.cpp

CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/EasySFML.cpp > CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.i

CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/EasySFML.cpp -o CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.s

CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o: IUIElement.cpp
CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o -MF CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/IUIElement.cpp

CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/IUIElement.cpp > CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.i

CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/IUIElement.cpp -o CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.s

CMakeFiles/Star_Dodgers.dir/Source.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/Source.cpp.o: Source.cpp
CMakeFiles/Star_Dodgers.dir/Source.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Star_Dodgers.dir/Source.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/Source.cpp.o -MF CMakeFiles/Star_Dodgers.dir/Source.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/Source.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp

CMakeFiles/Star_Dodgers.dir/Source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/Source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp > CMakeFiles/Star_Dodgers.dir/Source.cpp.i

CMakeFiles/Star_Dodgers.dir/Source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/Source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Source.cpp -o CMakeFiles/Star_Dodgers.dir/Source.cpp.s

CMakeFiles/Star_Dodgers.dir/Test.cpp.o: CMakeFiles/Star_Dodgers.dir/flags.make
CMakeFiles/Star_Dodgers.dir/Test.cpp.o: Test.cpp
CMakeFiles/Star_Dodgers.dir/Test.cpp.o: CMakeFiles/Star_Dodgers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Star_Dodgers.dir/Test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Star_Dodgers.dir/Test.cpp.o -MF CMakeFiles/Star_Dodgers.dir/Test.cpp.o.d -o CMakeFiles/Star_Dodgers.dir/Test.cpp.o -c /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Test.cpp

CMakeFiles/Star_Dodgers.dir/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Star_Dodgers.dir/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Test.cpp > CMakeFiles/Star_Dodgers.dir/Test.cpp.i

CMakeFiles/Star_Dodgers.dir/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Star_Dodgers.dir/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/Test.cpp -o CMakeFiles/Star_Dodgers.dir/Test.cpp.s

# Object files for target Star_Dodgers
Star_Dodgers_OBJECTS = \
"CMakeFiles/Star_Dodgers.dir/CBall.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/Source.cpp.o" \
"CMakeFiles/Star_Dodgers.dir/Test.cpp.o"

# External object files for target Star_Dodgers
Star_Dodgers_EXTERNAL_OBJECTS =

Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CBall.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CControlsMenu.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CGameManager.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CGameScene.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CGamepad.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CLobby.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CMainMenu.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CPlayer.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CResourceHolder.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CTeamsManager.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/CUIBar.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/EasySFML.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/IUIElement.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/Source.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/Test.cpp.o
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/build.make
Star_Dodgers: /usr/lib/libsfml-graphics.so.2.5.1
Star_Dodgers: /usr/lib/libsfml-window.so.2.5.1
Star_Dodgers: /usr/lib/libsfml-system.so.2.5.1
Star_Dodgers: CMakeFiles/Star_Dodgers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Star_Dodgers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Star_Dodgers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Star_Dodgers.dir/build: Star_Dodgers
.PHONY : CMakeFiles/Star_Dodgers.dir/build

CMakeFiles/Star_Dodgers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Star_Dodgers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Star_Dodgers.dir/clean

CMakeFiles/Star_Dodgers.dir/depend:
	cd /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers /home/neryst/Documents/Repos/Star_Dodgers/Star_Dodgers/CMakeFiles/Star_Dodgers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Star_Dodgers.dir/depend

