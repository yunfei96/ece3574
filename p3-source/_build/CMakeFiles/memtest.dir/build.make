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
CMAKE_SOURCE_DIR = /vagrant

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /vagrant/_build

# Utility rule file for memtest.

# Include the progress variables for this target.
include CMakeFiles/memtest.dir/progress.make

CMakeFiles/memtest:
	valgrind /vagrant/_build/unittests

memtest: CMakeFiles/memtest
memtest: CMakeFiles/memtest.dir/build.make

.PHONY : memtest

# Rule to build all files generated by this target.
CMakeFiles/memtest.dir/build: memtest

.PHONY : CMakeFiles/memtest.dir/build

CMakeFiles/memtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memtest.dir/clean

CMakeFiles/memtest.dir/depend:
	cd /vagrant/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /vagrant /vagrant /vagrant/_build /vagrant/_build /vagrant/_build/CMakeFiles/memtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/memtest.dir/depend

