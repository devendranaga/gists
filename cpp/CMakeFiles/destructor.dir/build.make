# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/devnaga/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/devnaga/cpp

# Include any dependencies generated for this target.
include CMakeFiles/destructor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/destructor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/destructor.dir/flags.make

CMakeFiles/destructor.dir/destructor.o: CMakeFiles/destructor.dir/flags.make
CMakeFiles/destructor.dir/destructor.o: destructor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/devnaga/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/destructor.dir/destructor.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/destructor.dir/destructor.o -c /home/devnaga/cpp/destructor.cpp

CMakeFiles/destructor.dir/destructor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/destructor.dir/destructor.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/devnaga/cpp/destructor.cpp > CMakeFiles/destructor.dir/destructor.i

CMakeFiles/destructor.dir/destructor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/destructor.dir/destructor.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/devnaga/cpp/destructor.cpp -o CMakeFiles/destructor.dir/destructor.s

CMakeFiles/destructor.dir/destructor.o.requires:

.PHONY : CMakeFiles/destructor.dir/destructor.o.requires

CMakeFiles/destructor.dir/destructor.o.provides: CMakeFiles/destructor.dir/destructor.o.requires
	$(MAKE) -f CMakeFiles/destructor.dir/build.make CMakeFiles/destructor.dir/destructor.o.provides.build
.PHONY : CMakeFiles/destructor.dir/destructor.o.provides

CMakeFiles/destructor.dir/destructor.o.provides.build: CMakeFiles/destructor.dir/destructor.o


# Object files for target destructor
destructor_OBJECTS = \
"CMakeFiles/destructor.dir/destructor.o"

# External object files for target destructor
destructor_EXTERNAL_OBJECTS =

destructor: CMakeFiles/destructor.dir/destructor.o
destructor: CMakeFiles/destructor.dir/build.make
destructor: CMakeFiles/destructor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/devnaga/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable destructor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/destructor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/destructor.dir/build: destructor

.PHONY : CMakeFiles/destructor.dir/build

CMakeFiles/destructor.dir/requires: CMakeFiles/destructor.dir/destructor.o.requires

.PHONY : CMakeFiles/destructor.dir/requires

CMakeFiles/destructor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/destructor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/destructor.dir/clean

CMakeFiles/destructor.dir/depend:
	cd /home/devnaga/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/devnaga/cpp /home/devnaga/cpp /home/devnaga/cpp /home/devnaga/cpp /home/devnaga/cpp/CMakeFiles/destructor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/destructor.dir/depend

