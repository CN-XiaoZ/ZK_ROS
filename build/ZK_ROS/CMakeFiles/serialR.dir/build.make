# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/zyc/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyc/catkin_ws/build

# Include any dependencies generated for this target.
include ZK_ROS/CMakeFiles/serialR.dir/depend.make

# Include the progress variables for this target.
include ZK_ROS/CMakeFiles/serialR.dir/progress.make

# Include the compile flags for this target's objects.
include ZK_ROS/CMakeFiles/serialR.dir/flags.make

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o: ZK_ROS/CMakeFiles/serialR.dir/flags.make
ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o: /home/zyc/catkin_ws/src/ZK_ROS/src/serialRW.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zyc/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o"
	cd /home/zyc/catkin_ws/build/ZK_ROS && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serialR.dir/src/serialRW.cpp.o -c /home/zyc/catkin_ws/src/ZK_ROS/src/serialRW.cpp

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serialR.dir/src/serialRW.cpp.i"
	cd /home/zyc/catkin_ws/build/ZK_ROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zyc/catkin_ws/src/ZK_ROS/src/serialRW.cpp > CMakeFiles/serialR.dir/src/serialRW.cpp.i

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serialR.dir/src/serialRW.cpp.s"
	cd /home/zyc/catkin_ws/build/ZK_ROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zyc/catkin_ws/src/ZK_ROS/src/serialRW.cpp -o CMakeFiles/serialR.dir/src/serialRW.cpp.s

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.requires:

.PHONY : ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.requires

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.provides: ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.requires
	$(MAKE) -f ZK_ROS/CMakeFiles/serialR.dir/build.make ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.provides.build
.PHONY : ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.provides

ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.provides.build: ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o


# Object files for target serialR
serialR_OBJECTS = \
"CMakeFiles/serialR.dir/src/serialRW.cpp.o"

# External object files for target serialR
serialR_EXTERNAL_OBJECTS =

/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: ZK_ROS/CMakeFiles/serialR.dir/build.make
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/libroscpp.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/librosconsole.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/librostime.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /opt/ros/melodic/lib/libcpp_common.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR: ZK_ROS/CMakeFiles/serialR.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zyc/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR"
	cd /home/zyc/catkin_ws/build/ZK_ROS && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialR.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ZK_ROS/CMakeFiles/serialR.dir/build: /home/zyc/catkin_ws/devel/lib/ZK_ROS/serialR

.PHONY : ZK_ROS/CMakeFiles/serialR.dir/build

ZK_ROS/CMakeFiles/serialR.dir/requires: ZK_ROS/CMakeFiles/serialR.dir/src/serialRW.cpp.o.requires

.PHONY : ZK_ROS/CMakeFiles/serialR.dir/requires

ZK_ROS/CMakeFiles/serialR.dir/clean:
	cd /home/zyc/catkin_ws/build/ZK_ROS && $(CMAKE_COMMAND) -P CMakeFiles/serialR.dir/cmake_clean.cmake
.PHONY : ZK_ROS/CMakeFiles/serialR.dir/clean

ZK_ROS/CMakeFiles/serialR.dir/depend:
	cd /home/zyc/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyc/catkin_ws/src /home/zyc/catkin_ws/src/ZK_ROS /home/zyc/catkin_ws/build /home/zyc/catkin_ws/build/ZK_ROS /home/zyc/catkin_ws/build/ZK_ROS/CMakeFiles/serialR.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ZK_ROS/CMakeFiles/serialR.dir/depend

