# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/prox/Praktikum2_bck

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/prox/Praktikum2_bck/build

# Include any dependencies generated for this target.
include CMakeFiles/p2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p2.dir/flags.make

CMakeFiles/p2.dir/src/p2.o: CMakeFiles/p2.dir/flags.make
CMakeFiles/p2.dir/src/p2.o: ../src/p2.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/prox/Praktikum2_bck/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/p2.dir/src/p2.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/p2.dir/src/p2.o   -c /home/prox/Praktikum2_bck/src/p2.c

CMakeFiles/p2.dir/src/p2.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p2.dir/src/p2.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/prox/Praktikum2_bck/src/p2.c > CMakeFiles/p2.dir/src/p2.i

CMakeFiles/p2.dir/src/p2.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p2.dir/src/p2.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/prox/Praktikum2_bck/src/p2.c -o CMakeFiles/p2.dir/src/p2.s

CMakeFiles/p2.dir/src/p2.o.requires:
.PHONY : CMakeFiles/p2.dir/src/p2.o.requires

CMakeFiles/p2.dir/src/p2.o.provides: CMakeFiles/p2.dir/src/p2.o.requires
	$(MAKE) -f CMakeFiles/p2.dir/build.make CMakeFiles/p2.dir/src/p2.o.provides.build
.PHONY : CMakeFiles/p2.dir/src/p2.o.provides

CMakeFiles/p2.dir/src/p2.o.provides.build: CMakeFiles/p2.dir/src/p2.o

CMakeFiles/p2.dir/src/pgm.o: CMakeFiles/p2.dir/flags.make
CMakeFiles/p2.dir/src/pgm.o: ../src/pgm.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/prox/Praktikum2_bck/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/p2.dir/src/pgm.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/p2.dir/src/pgm.o   -c /home/prox/Praktikum2_bck/src/pgm.c

CMakeFiles/p2.dir/src/pgm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p2.dir/src/pgm.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/prox/Praktikum2_bck/src/pgm.c > CMakeFiles/p2.dir/src/pgm.i

CMakeFiles/p2.dir/src/pgm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p2.dir/src/pgm.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/prox/Praktikum2_bck/src/pgm.c -o CMakeFiles/p2.dir/src/pgm.s

CMakeFiles/p2.dir/src/pgm.o.requires:
.PHONY : CMakeFiles/p2.dir/src/pgm.o.requires

CMakeFiles/p2.dir/src/pgm.o.provides: CMakeFiles/p2.dir/src/pgm.o.requires
	$(MAKE) -f CMakeFiles/p2.dir/build.make CMakeFiles/p2.dir/src/pgm.o.provides.build
.PHONY : CMakeFiles/p2.dir/src/pgm.o.provides

CMakeFiles/p2.dir/src/pgm.o.provides.build: CMakeFiles/p2.dir/src/pgm.o

# Object files for target p2
p2_OBJECTS = \
"CMakeFiles/p2.dir/src/p2.o" \
"CMakeFiles/p2.dir/src/pgm.o"

# External object files for target p2
p2_EXTERNAL_OBJECTS =

../bin/p2: CMakeFiles/p2.dir/src/p2.o
../bin/p2: CMakeFiles/p2.dir/src/pgm.o
../bin/p2: CMakeFiles/p2.dir/build.make
../bin/p2: CMakeFiles/p2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/p2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p2.dir/build: ../bin/p2
.PHONY : CMakeFiles/p2.dir/build

CMakeFiles/p2.dir/requires: CMakeFiles/p2.dir/src/p2.o.requires
CMakeFiles/p2.dir/requires: CMakeFiles/p2.dir/src/pgm.o.requires
.PHONY : CMakeFiles/p2.dir/requires

CMakeFiles/p2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p2.dir/clean

CMakeFiles/p2.dir/depend:
	cd /home/prox/Praktikum2_bck/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/prox/Praktikum2_bck /home/prox/Praktikum2_bck /home/prox/Praktikum2_bck/build /home/prox/Praktikum2_bck/build /home/prox/Praktikum2_bck/build/CMakeFiles/p2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p2.dir/depend

