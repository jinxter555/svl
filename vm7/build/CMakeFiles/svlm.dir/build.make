# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/jt/projects/cpp/t/parse_vm7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jt/projects/cpp/t/parse_vm7/build

# Include any dependencies generated for this target.
include CMakeFiles/svlm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/svlm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/svlm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/svlm.dir/flags.make

CMakeFiles/svlm.dir/main.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/main.cc.o: ../main.cc
CMakeFiles/svlm.dir/main.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/svlm.dir/main.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/main.cc.o -MF CMakeFiles/svlm.dir/main.cc.o.d -o CMakeFiles/svlm.dir/main.cc.o -c /home/jt/projects/cpp/t/parse_vm7/main.cc

CMakeFiles/svlm.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/main.cc > CMakeFiles/svlm.dir/main.cc.i

CMakeFiles/svlm.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/main.cc -o CMakeFiles/svlm.dir/main.cc.s

CMakeFiles/svlm.dir/svlm_parser.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/svlm_parser.cc.o: ../svlm_parser.cc
CMakeFiles/svlm.dir/svlm_parser.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/svlm.dir/svlm_parser.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/svlm_parser.cc.o -MF CMakeFiles/svlm.dir/svlm_parser.cc.o.d -o CMakeFiles/svlm.dir/svlm_parser.cc.o -c /home/jt/projects/cpp/t/parse_vm7/svlm_parser.cc

CMakeFiles/svlm.dir/svlm_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/svlm_parser.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/svlm_parser.cc > CMakeFiles/svlm.dir/svlm_parser.cc.i

CMakeFiles/svlm.dir/svlm_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/svlm_parser.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/svlm_parser.cc -o CMakeFiles/svlm.dir/svlm_parser.cc.s

CMakeFiles/svlm.dir/svlm_ast.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/svlm_ast.cc.o: ../svlm_ast.cc
CMakeFiles/svlm.dir/svlm_ast.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/svlm.dir/svlm_ast.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/svlm_ast.cc.o -MF CMakeFiles/svlm.dir/svlm_ast.cc.o.d -o CMakeFiles/svlm.dir/svlm_ast.cc.o -c /home/jt/projects/cpp/t/parse_vm7/svlm_ast.cc

CMakeFiles/svlm.dir/svlm_ast.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/svlm_ast.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/svlm_ast.cc > CMakeFiles/svlm.dir/svlm_ast.cc.i

CMakeFiles/svlm.dir/svlm_ast.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/svlm_ast.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/svlm_ast.cc -o CMakeFiles/svlm.dir/svlm_ast.cc.s

CMakeFiles/svlm.dir/svlm_interactive.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/svlm_interactive.cc.o: ../svlm_interactive.cc
CMakeFiles/svlm.dir/svlm_interactive.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/svlm.dir/svlm_interactive.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/svlm_interactive.cc.o -MF CMakeFiles/svlm.dir/svlm_interactive.cc.o.d -o CMakeFiles/svlm.dir/svlm_interactive.cc.o -c /home/jt/projects/cpp/t/parse_vm7/svlm_interactive.cc

CMakeFiles/svlm.dir/svlm_interactive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/svlm_interactive.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/svlm_interactive.cc > CMakeFiles/svlm.dir/svlm_interactive.cc.i

CMakeFiles/svlm.dir/svlm_interactive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/svlm_interactive.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/svlm_interactive.cc -o CMakeFiles/svlm.dir/svlm_interactive.cc.s

CMakeFiles/svlm.dir/svlm_scanner.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/svlm_scanner.cc.o: ../svlm_scanner.cc
CMakeFiles/svlm.dir/svlm_scanner.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/svlm.dir/svlm_scanner.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/svlm_scanner.cc.o -MF CMakeFiles/svlm.dir/svlm_scanner.cc.o.d -o CMakeFiles/svlm.dir/svlm_scanner.cc.o -c /home/jt/projects/cpp/t/parse_vm7/svlm_scanner.cc

CMakeFiles/svlm.dir/svlm_scanner.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/svlm_scanner.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/svlm_scanner.cc > CMakeFiles/svlm.dir/svlm_scanner.cc.i

CMakeFiles/svlm.dir/svlm_scanner.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/svlm_scanner.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/svlm_scanner.cc -o CMakeFiles/svlm.dir/svlm_scanner.cc.s

CMakeFiles/svlm.dir/prompt.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/prompt.cc.o: ../prompt.cc
CMakeFiles/svlm.dir/prompt.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/svlm.dir/prompt.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/prompt.cc.o -MF CMakeFiles/svlm.dir/prompt.cc.o.d -o CMakeFiles/svlm.dir/prompt.cc.o -c /home/jt/projects/cpp/t/parse_vm7/prompt.cc

CMakeFiles/svlm.dir/prompt.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/prompt.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/prompt.cc > CMakeFiles/svlm.dir/prompt.cc.i

CMakeFiles/svlm.dir/prompt.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/prompt.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/prompt.cc -o CMakeFiles/svlm.dir/prompt.cc.s

CMakeFiles/svlm.dir/commandline.cc.o: CMakeFiles/svlm.dir/flags.make
CMakeFiles/svlm.dir/commandline.cc.o: ../commandline.cc
CMakeFiles/svlm.dir/commandline.cc.o: CMakeFiles/svlm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/svlm.dir/commandline.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/svlm.dir/commandline.cc.o -MF CMakeFiles/svlm.dir/commandline.cc.o.d -o CMakeFiles/svlm.dir/commandline.cc.o -c /home/jt/projects/cpp/t/parse_vm7/commandline.cc

CMakeFiles/svlm.dir/commandline.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svlm.dir/commandline.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jt/projects/cpp/t/parse_vm7/commandline.cc > CMakeFiles/svlm.dir/commandline.cc.i

CMakeFiles/svlm.dir/commandline.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svlm.dir/commandline.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jt/projects/cpp/t/parse_vm7/commandline.cc -o CMakeFiles/svlm.dir/commandline.cc.s

# Object files for target svlm
svlm_OBJECTS = \
"CMakeFiles/svlm.dir/main.cc.o" \
"CMakeFiles/svlm.dir/svlm_parser.cc.o" \
"CMakeFiles/svlm.dir/svlm_ast.cc.o" \
"CMakeFiles/svlm.dir/svlm_interactive.cc.o" \
"CMakeFiles/svlm.dir/svlm_scanner.cc.o" \
"CMakeFiles/svlm.dir/prompt.cc.o" \
"CMakeFiles/svlm.dir/commandline.cc.o"

# External object files for target svlm
svlm_EXTERNAL_OBJECTS =

svlm: CMakeFiles/svlm.dir/main.cc.o
svlm: CMakeFiles/svlm.dir/svlm_parser.cc.o
svlm: CMakeFiles/svlm.dir/svlm_ast.cc.o
svlm: CMakeFiles/svlm.dir/svlm_interactive.cc.o
svlm: CMakeFiles/svlm.dir/svlm_scanner.cc.o
svlm: CMakeFiles/svlm.dir/prompt.cc.o
svlm: CMakeFiles/svlm.dir/commandline.cc.o
svlm: CMakeFiles/svlm.dir/build.make
svlm: libsvlm-node.a
svlm: libsvlm-logger.a
svlm: /usr/lib/x86_64-linux-gnu/libreadline.so
svlm: CMakeFiles/svlm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable svlm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/svlm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/svlm.dir/build: svlm
.PHONY : CMakeFiles/svlm.dir/build

CMakeFiles/svlm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/svlm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/svlm.dir/clean

CMakeFiles/svlm.dir/depend:
	cd /home/jt/projects/cpp/t/parse_vm7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jt/projects/cpp/t/parse_vm7 /home/jt/projects/cpp/t/parse_vm7 /home/jt/projects/cpp/t/parse_vm7/build /home/jt/projects/cpp/t/parse_vm7/build /home/jt/projects/cpp/t/parse_vm7/build/CMakeFiles/svlm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/svlm.dir/depend

