# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /home/japesh/.local/lib/python3.7/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/japesh/.local/lib/python3.7/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/japesh/rws/jenkins/jenkins_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/japesh/rws/jenkins/jenkins_test/build

# Include any dependencies generated for this target.
include CMakeFiles/waresense.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/waresense.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/waresense.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/waresense.dir/flags.make

CMakeFiles/waresense.dir/src/ApiController.cpp.o: CMakeFiles/waresense.dir/flags.make
CMakeFiles/waresense.dir/src/ApiController.cpp.o: /home/japesh/rws/jenkins/jenkins_test/src/ApiController.cpp
CMakeFiles/waresense.dir/src/ApiController.cpp.o: CMakeFiles/waresense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/japesh/rws/jenkins/jenkins_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/waresense.dir/src/ApiController.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/waresense.dir/src/ApiController.cpp.o -MF CMakeFiles/waresense.dir/src/ApiController.cpp.o.d -o CMakeFiles/waresense.dir/src/ApiController.cpp.o -c /home/japesh/rws/jenkins/jenkins_test/src/ApiController.cpp

CMakeFiles/waresense.dir/src/ApiController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waresense.dir/src/ApiController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/japesh/rws/jenkins/jenkins_test/src/ApiController.cpp > CMakeFiles/waresense.dir/src/ApiController.cpp.i

CMakeFiles/waresense.dir/src/ApiController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waresense.dir/src/ApiController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/japesh/rws/jenkins/jenkins_test/src/ApiController.cpp -o CMakeFiles/waresense.dir/src/ApiController.cpp.s

# Object files for target waresense
waresense_OBJECTS = \
"CMakeFiles/waresense.dir/src/ApiController.cpp.o"

# External object files for target waresense
waresense_EXTERNAL_OBJECTS =

waresense: CMakeFiles/waresense.dir/src/ApiController.cpp.o
waresense: CMakeFiles/waresense.dir/build.make
waresense: /usr/lib/x86_64-linux-gnu/libboost_system.so
waresense: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
waresense: /usr/local/lib/libmongocxx.so.3.6.5
waresense: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
waresense: /usr/lib/x86_64-linux-gnu/libboost_system.so
waresense: /usr/local/lib/libbsoncxx.so.3.6.5
waresense: CMakeFiles/waresense.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/japesh/rws/jenkins/jenkins_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable waresense"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/waresense.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/waresense.dir/build: waresense
.PHONY : CMakeFiles/waresense.dir/build

CMakeFiles/waresense.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/waresense.dir/cmake_clean.cmake
.PHONY : CMakeFiles/waresense.dir/clean

CMakeFiles/waresense.dir/depend:
	cd /home/japesh/rws/jenkins/jenkins_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/japesh/rws/jenkins/jenkins_test /home/japesh/rws/jenkins/jenkins_test /home/japesh/rws/jenkins/jenkins_test/build /home/japesh/rws/jenkins/jenkins_test/build /home/japesh/rws/jenkins/jenkins_test/build/CMakeFiles/waresense.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/waresense.dir/depend

