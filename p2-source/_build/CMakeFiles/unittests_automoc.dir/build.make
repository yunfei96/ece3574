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

# Utility rule file for unittests_automoc.

# Include the progress variables for this target.
include CMakeFiles/unittests_automoc.dir/progress.make

CMakeFiles/unittests_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/vagrant/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target unittests"
	/usr/bin/cmake -E cmake_autogen /vagrant/_build/CMakeFiles/unittests_automoc.dir/ ""

unittests_automoc: CMakeFiles/unittests_automoc
unittests_automoc: CMakeFiles/unittests_automoc.dir/build.make

.PHONY : unittests_automoc

# Rule to build all files generated by this target.
CMakeFiles/unittests_automoc.dir/build: unittests_automoc

.PHONY : CMakeFiles/unittests_automoc.dir/build

CMakeFiles/unittests_automoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unittests_automoc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unittests_automoc.dir/clean

CMakeFiles/unittests_automoc.dir/depend:
	cd /vagrant/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /vagrant /vagrant /vagrant/_build /vagrant/_build /vagrant/_build/CMakeFiles/unittests_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unittests_automoc.dir/depend

