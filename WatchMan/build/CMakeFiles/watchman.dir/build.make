# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hvn1/code/Algorithms/WatchMan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hvn1/code/Algorithms/WatchMan/build

# Include any dependencies generated for this target.
include CMakeFiles/watchman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/watchman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/watchman.dir/flags.make

CMakeFiles/watchman.dir/main.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/main.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/main.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/main.cpp

CMakeFiles/watchman.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/main.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/main.cpp > CMakeFiles/watchman.dir/main.cpp.i

CMakeFiles/watchman.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/main.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/main.cpp -o CMakeFiles/watchman.dir/main.cpp.s

CMakeFiles/watchman.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/main.cpp.o.requires

CMakeFiles/watchman.dir/main.cpp.o.provides: CMakeFiles/watchman.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/main.cpp.o.provides

CMakeFiles/watchman.dir/main.cpp.o.provides.build: CMakeFiles/watchman.dir/main.cpp.o

CMakeFiles/watchman.dir/bfs.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/bfs.cpp.o: ../bfs.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/bfs.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/bfs.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/bfs.cpp

CMakeFiles/watchman.dir/bfs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/bfs.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/bfs.cpp > CMakeFiles/watchman.dir/bfs.cpp.i

CMakeFiles/watchman.dir/bfs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/bfs.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/bfs.cpp -o CMakeFiles/watchman.dir/bfs.cpp.s

CMakeFiles/watchman.dir/bfs.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/bfs.cpp.o.requires

CMakeFiles/watchman.dir/bfs.cpp.o.provides: CMakeFiles/watchman.dir/bfs.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/bfs.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/bfs.cpp.o.provides

CMakeFiles/watchman.dir/bfs.cpp.o.provides.build: CMakeFiles/watchman.dir/bfs.cpp.o

CMakeFiles/watchman.dir/parsing.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/parsing.cpp.o: ../parsing.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/parsing.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/parsing.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/parsing.cpp

CMakeFiles/watchman.dir/parsing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/parsing.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/parsing.cpp > CMakeFiles/watchman.dir/parsing.cpp.i

CMakeFiles/watchman.dir/parsing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/parsing.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/parsing.cpp -o CMakeFiles/watchman.dir/parsing.cpp.s

CMakeFiles/watchman.dir/parsing.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/parsing.cpp.o.requires

CMakeFiles/watchman.dir/parsing.cpp.o.provides: CMakeFiles/watchman.dir/parsing.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/parsing.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/parsing.cpp.o.provides

CMakeFiles/watchman.dir/parsing.cpp.o.provides.build: CMakeFiles/watchman.dir/parsing.cpp.o

CMakeFiles/watchman.dir/intersection.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/intersection.cpp.o: ../intersection.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/intersection.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/intersection.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/intersection.cpp

CMakeFiles/watchman.dir/intersection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/intersection.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/intersection.cpp > CMakeFiles/watchman.dir/intersection.cpp.i

CMakeFiles/watchman.dir/intersection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/intersection.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/intersection.cpp -o CMakeFiles/watchman.dir/intersection.cpp.s

CMakeFiles/watchman.dir/intersection.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/intersection.cpp.o.requires

CMakeFiles/watchman.dir/intersection.cpp.o.provides: CMakeFiles/watchman.dir/intersection.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/intersection.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/intersection.cpp.o.provides

CMakeFiles/watchman.dir/intersection.cpp.o.provides.build: CMakeFiles/watchman.dir/intersection.cpp.o

CMakeFiles/watchman.dir/ffs.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/ffs.cpp.o: ../ffs.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/ffs.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/ffs.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/ffs.cpp

CMakeFiles/watchman.dir/ffs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/ffs.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/ffs.cpp > CMakeFiles/watchman.dir/ffs.cpp.i

CMakeFiles/watchman.dir/ffs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/ffs.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/ffs.cpp -o CMakeFiles/watchman.dir/ffs.cpp.s

CMakeFiles/watchman.dir/ffs.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/ffs.cpp.o.requires

CMakeFiles/watchman.dir/ffs.cpp.o.provides: CMakeFiles/watchman.dir/ffs.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/ffs.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/ffs.cpp.o.provides

CMakeFiles/watchman.dir/ffs.cpp.o.provides.build: CMakeFiles/watchman.dir/ffs.cpp.o

CMakeFiles/watchman.dir/watchman.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/watchman.cpp.o: ../watchman.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/watchman.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/watchman.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/watchman.cpp

CMakeFiles/watchman.dir/watchman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/watchman.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/watchman.cpp > CMakeFiles/watchman.dir/watchman.cpp.i

CMakeFiles/watchman.dir/watchman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/watchman.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/watchman.cpp -o CMakeFiles/watchman.dir/watchman.cpp.s

CMakeFiles/watchman.dir/watchman.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/watchman.cpp.o.requires

CMakeFiles/watchman.dir/watchman.cpp.o.provides: CMakeFiles/watchman.dir/watchman.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/watchman.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/watchman.cpp.o.provides

CMakeFiles/watchman.dir/watchman.cpp.o.provides.build: CMakeFiles/watchman.dir/watchman.cpp.o

CMakeFiles/watchman.dir/inputData.cpp.o: CMakeFiles/watchman.dir/flags.make
CMakeFiles/watchman.dir/inputData.cpp.o: ../inputData.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watchman.dir/inputData.cpp.o"
	/usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/watchman.dir/inputData.cpp.o -c /home/hvn1/code/Algorithms/WatchMan/inputData.cpp

CMakeFiles/watchman.dir/inputData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watchman.dir/inputData.cpp.i"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hvn1/code/Algorithms/WatchMan/inputData.cpp > CMakeFiles/watchman.dir/inputData.cpp.i

CMakeFiles/watchman.dir/inputData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watchman.dir/inputData.cpp.s"
	/usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hvn1/code/Algorithms/WatchMan/inputData.cpp -o CMakeFiles/watchman.dir/inputData.cpp.s

CMakeFiles/watchman.dir/inputData.cpp.o.requires:
.PHONY : CMakeFiles/watchman.dir/inputData.cpp.o.requires

CMakeFiles/watchman.dir/inputData.cpp.o.provides: CMakeFiles/watchman.dir/inputData.cpp.o.requires
	$(MAKE) -f CMakeFiles/watchman.dir/build.make CMakeFiles/watchman.dir/inputData.cpp.o.provides.build
.PHONY : CMakeFiles/watchman.dir/inputData.cpp.o.provides

CMakeFiles/watchman.dir/inputData.cpp.o.provides.build: CMakeFiles/watchman.dir/inputData.cpp.o

# Object files for target watchman
watchman_OBJECTS = \
"CMakeFiles/watchman.dir/main.cpp.o" \
"CMakeFiles/watchman.dir/bfs.cpp.o" \
"CMakeFiles/watchman.dir/parsing.cpp.o" \
"CMakeFiles/watchman.dir/intersection.cpp.o" \
"CMakeFiles/watchman.dir/ffs.cpp.o" \
"CMakeFiles/watchman.dir/watchman.cpp.o" \
"CMakeFiles/watchman.dir/inputData.cpp.o"

# External object files for target watchman
watchman_EXTERNAL_OBJECTS =

watchman: CMakeFiles/watchman.dir/main.cpp.o
watchman: CMakeFiles/watchman.dir/bfs.cpp.o
watchman: CMakeFiles/watchman.dir/parsing.cpp.o
watchman: CMakeFiles/watchman.dir/intersection.cpp.o
watchman: CMakeFiles/watchman.dir/ffs.cpp.o
watchman: CMakeFiles/watchman.dir/watchman.cpp.o
watchman: CMakeFiles/watchman.dir/inputData.cpp.o
watchman: CMakeFiles/watchman.dir/build.make
watchman: CMakeFiles/watchman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable watchman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/watchman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/watchman.dir/build: watchman
.PHONY : CMakeFiles/watchman.dir/build

CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/main.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/bfs.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/parsing.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/intersection.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/ffs.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/watchman.cpp.o.requires
CMakeFiles/watchman.dir/requires: CMakeFiles/watchman.dir/inputData.cpp.o.requires
.PHONY : CMakeFiles/watchman.dir/requires

CMakeFiles/watchman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/watchman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/watchman.dir/clean

CMakeFiles/watchman.dir/depend:
	cd /home/hvn1/code/Algorithms/WatchMan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hvn1/code/Algorithms/WatchMan /home/hvn1/code/Algorithms/WatchMan /home/hvn1/code/Algorithms/WatchMan/build /home/hvn1/code/Algorithms/WatchMan/build /home/hvn1/code/Algorithms/WatchMan/build/CMakeFiles/watchman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/watchman.dir/depend

