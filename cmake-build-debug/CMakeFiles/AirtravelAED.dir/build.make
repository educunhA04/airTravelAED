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
CMAKE_SOURCE_DIR = /home/magui/Documents/AED/PROJECTS/airTravelAED

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AirtravelAED.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AirtravelAED.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AirtravelAED.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AirtravelAED.dir/flags.make

CMakeFiles/AirtravelAED.dir/main.cpp.o: CMakeFiles/AirtravelAED.dir/flags.make
CMakeFiles/AirtravelAED.dir/main.cpp.o: ../main.cpp
CMakeFiles/AirtravelAED.dir/main.cpp.o: CMakeFiles/AirtravelAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AirtravelAED.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AirtravelAED.dir/main.cpp.o -MF CMakeFiles/AirtravelAED.dir/main.cpp.o.d -o CMakeFiles/AirtravelAED.dir/main.cpp.o -c /home/magui/Documents/AED/PROJECTS/airTravelAED/main.cpp

CMakeFiles/AirtravelAED.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirtravelAED.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magui/Documents/AED/PROJECTS/airTravelAED/main.cpp > CMakeFiles/AirtravelAED.dir/main.cpp.i

CMakeFiles/AirtravelAED.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirtravelAED.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magui/Documents/AED/PROJECTS/airTravelAED/main.cpp -o CMakeFiles/AirtravelAED.dir/main.cpp.s

CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o: CMakeFiles/AirtravelAED.dir/flags.make
CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o: ../Classes/airport.cpp
CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o: CMakeFiles/AirtravelAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o -MF CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o.d -o CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o -c /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airport.cpp

CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airport.cpp > CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.i

CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airport.cpp -o CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.s

CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o: CMakeFiles/AirtravelAED.dir/flags.make
CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o: ../Classes/airlines.cpp
CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o: CMakeFiles/AirtravelAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o -MF CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o.d -o CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o -c /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airlines.cpp

CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airlines.cpp > CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.i

CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/airlines.cpp -o CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.s

CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o: CMakeFiles/AirtravelAED.dir/flags.make
CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o: ../Classes/read.cpp
CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o: CMakeFiles/AirtravelAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o -MF CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o.d -o CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o -c /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/read.cpp

CMakeFiles/AirtravelAED.dir/Classes/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirtravelAED.dir/Classes/read.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/read.cpp > CMakeFiles/AirtravelAED.dir/Classes/read.cpp.i

CMakeFiles/AirtravelAED.dir/Classes/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirtravelAED.dir/Classes/read.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/read.cpp -o CMakeFiles/AirtravelAED.dir/Classes/read.cpp.s

CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o: CMakeFiles/AirtravelAED.dir/flags.make
CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o: ../Classes/menu.cpp
CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o: CMakeFiles/AirtravelAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o -MF CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o.d -o CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o -c /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/menu.cpp

CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/menu.cpp > CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.i

CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magui/Documents/AED/PROJECTS/airTravelAED/Classes/menu.cpp -o CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.s

# Object files for target AirtravelAED
AirtravelAED_OBJECTS = \
"CMakeFiles/AirtravelAED.dir/main.cpp.o" \
"CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o" \
"CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o" \
"CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o" \
"CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o"

# External object files for target AirtravelAED
AirtravelAED_EXTERNAL_OBJECTS =

AirtravelAED: CMakeFiles/AirtravelAED.dir/main.cpp.o
AirtravelAED: CMakeFiles/AirtravelAED.dir/Classes/airport.cpp.o
AirtravelAED: CMakeFiles/AirtravelAED.dir/Classes/airlines.cpp.o
AirtravelAED: CMakeFiles/AirtravelAED.dir/Classes/read.cpp.o
AirtravelAED: CMakeFiles/AirtravelAED.dir/Classes/menu.cpp.o
AirtravelAED: CMakeFiles/AirtravelAED.dir/build.make
AirtravelAED: CMakeFiles/AirtravelAED.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable AirtravelAED"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AirtravelAED.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AirtravelAED.dir/build: AirtravelAED
.PHONY : CMakeFiles/AirtravelAED.dir/build

CMakeFiles/AirtravelAED.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AirtravelAED.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AirtravelAED.dir/clean

CMakeFiles/AirtravelAED.dir/depend:
	cd /home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/magui/Documents/AED/PROJECTS/airTravelAED /home/magui/Documents/AED/PROJECTS/airTravelAED /home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug /home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug /home/magui/Documents/AED/PROJECTS/airTravelAED/cmake-build-debug/CMakeFiles/AirtravelAED.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AirtravelAED.dir/depend
