# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/flo/delivery/trimestre5/RType/R-type

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/flo/delivery/trimestre5/RType/R-type/.Build

# Include any dependencies generated for this target.
include src/server/game/CMakeFiles/GameServerLibrary.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/server/game/CMakeFiles/GameServerLibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include src/server/game/CMakeFiles/GameServerLibrary.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/game/CMakeFiles/GameServerLibrary.dir/flags.make

src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o: src/server/game/CMakeFiles/GameServerLibrary.dir/flags.make
src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o: /home/flo/delivery/trimestre5/RType/R-type/src/server/game/game.cpp
src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o: src/server/game/CMakeFiles/GameServerLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flo/delivery/trimestre5/RType/R-type/.Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o"
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o -MF CMakeFiles/GameServerLibrary.dir/game.cpp.o.d -o CMakeFiles/GameServerLibrary.dir/game.cpp.o -c /home/flo/delivery/trimestre5/RType/R-type/src/server/game/game.cpp

src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameServerLibrary.dir/game.cpp.i"
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flo/delivery/trimestre5/RType/R-type/src/server/game/game.cpp > CMakeFiles/GameServerLibrary.dir/game.cpp.i

src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameServerLibrary.dir/game.cpp.s"
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flo/delivery/trimestre5/RType/R-type/src/server/game/game.cpp -o CMakeFiles/GameServerLibrary.dir/game.cpp.s

# Object files for target GameServerLibrary
GameServerLibrary_OBJECTS = \
"CMakeFiles/GameServerLibrary.dir/game.cpp.o"

# External object files for target GameServerLibrary
GameServerLibrary_EXTERNAL_OBJECTS =

src/server/game/libGameServerLibrary.a: src/server/game/CMakeFiles/GameServerLibrary.dir/game.cpp.o
src/server/game/libGameServerLibrary.a: src/server/game/CMakeFiles/GameServerLibrary.dir/build.make
src/server/game/libGameServerLibrary.a: src/server/game/CMakeFiles/GameServerLibrary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/flo/delivery/trimestre5/RType/R-type/.Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGameServerLibrary.a"
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && $(CMAKE_COMMAND) -P CMakeFiles/GameServerLibrary.dir/cmake_clean_target.cmake
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GameServerLibrary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/game/CMakeFiles/GameServerLibrary.dir/build: src/server/game/libGameServerLibrary.a
.PHONY : src/server/game/CMakeFiles/GameServerLibrary.dir/build

src/server/game/CMakeFiles/GameServerLibrary.dir/clean:
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game && $(CMAKE_COMMAND) -P CMakeFiles/GameServerLibrary.dir/cmake_clean.cmake
.PHONY : src/server/game/CMakeFiles/GameServerLibrary.dir/clean

src/server/game/CMakeFiles/GameServerLibrary.dir/depend:
	cd /home/flo/delivery/trimestre5/RType/R-type/.Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/flo/delivery/trimestre5/RType/R-type /home/flo/delivery/trimestre5/RType/R-type/src/server/game /home/flo/delivery/trimestre5/RType/R-type/.Build /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game /home/flo/delivery/trimestre5/RType/R-type/.Build/src/server/game/CMakeFiles/GameServerLibrary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/game/CMakeFiles/GameServerLibrary.dir/depend

