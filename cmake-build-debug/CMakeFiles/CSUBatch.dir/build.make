# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /cygdrive/c/Users/jazart/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/jazart/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/jazart/CLionProjects/CSUBatch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CSUBatch.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CSUBatch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CSUBatch.dir/flags.make

CMakeFiles/CSUBatch.dir/main.c.o: CMakeFiles/CSUBatch.dir/flags.make
CMakeFiles/CSUBatch.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CSUBatch.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSUBatch.dir/main.c.o   -c /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/main.c

CMakeFiles/CSUBatch.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSUBatch.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/main.c > CMakeFiles/CSUBatch.dir/main.c.i

CMakeFiles/CSUBatch.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSUBatch.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/main.c -o CMakeFiles/CSUBatch.dir/main.c.s

CMakeFiles/CSUBatch.dir/menu.c.o: CMakeFiles/CSUBatch.dir/flags.make
CMakeFiles/CSUBatch.dir/menu.c.o: ../menu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CSUBatch.dir/menu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSUBatch.dir/menu.c.o   -c /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/menu.c

CMakeFiles/CSUBatch.dir/menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSUBatch.dir/menu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/menu.c > CMakeFiles/CSUBatch.dir/menu.c.i

CMakeFiles/CSUBatch.dir/menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSUBatch.dir/menu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/menu.c -o CMakeFiles/CSUBatch.dir/menu.c.s

# Object files for target CSUBatch
CSUBatch_OBJECTS = \
"CMakeFiles/CSUBatch.dir/main.c.o" \
"CMakeFiles/CSUBatch.dir/menu.c.o"

# External object files for target CSUBatch
CSUBatch_EXTERNAL_OBJECTS =

CSUBatch.exe: CMakeFiles/CSUBatch.dir/main.c.o
CSUBatch.exe: CMakeFiles/CSUBatch.dir/menu.c.o
CSUBatch.exe: CMakeFiles/CSUBatch.dir/build.make
CSUBatch.exe: CMakeFiles/CSUBatch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable CSUBatch.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CSUBatch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CSUBatch.dir/build: CSUBatch.exe

.PHONY : CMakeFiles/CSUBatch.dir/build

CMakeFiles/CSUBatch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CSUBatch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CSUBatch.dir/clean

CMakeFiles/CSUBatch.dir/depend:
	cd /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/jazart/CLionProjects/CSUBatch /cygdrive/c/Users/jazart/CLionProjects/CSUBatch /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug /cygdrive/c/Users/jazart/CLionProjects/CSUBatch/cmake-build-debug/CMakeFiles/CSUBatch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CSUBatch.dir/depend

