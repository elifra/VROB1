# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/thomas/Documents/VROB1/VROB-code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Documents/VROB1/VROB-code

# Include any dependencies generated for this target.
include tp/CMakeFiles/tp_klt.dir/depend.make

# Include the progress variables for this target.
include tp/CMakeFiles/tp_klt.dir/progress.make

# Include the compile flags for this target's objects.
include tp/CMakeFiles/tp_klt.dir/flags.make

tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.o: tp/CMakeFiles/tp_klt.dir/flags.make
tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.o: tp/tp_klt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/Documents/VROB1/VROB-code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.o"
	cd /home/thomas/Documents/VROB1/VROB-code/tp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tp_klt.dir/tp_klt.cpp.o -c /home/thomas/Documents/VROB1/VROB-code/tp/tp_klt.cpp

tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp_klt.dir/tp_klt.cpp.i"
	cd /home/thomas/Documents/VROB1/VROB-code/tp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/Documents/VROB1/VROB-code/tp/tp_klt.cpp > CMakeFiles/tp_klt.dir/tp_klt.cpp.i

tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp_klt.dir/tp_klt.cpp.s"
	cd /home/thomas/Documents/VROB1/VROB-code/tp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/Documents/VROB1/VROB-code/tp/tp_klt.cpp -o CMakeFiles/tp_klt.dir/tp_klt.cpp.s

# Object files for target tp_klt
tp_klt_OBJECTS = \
"CMakeFiles/tp_klt.dir/tp_klt.cpp.o"

# External object files for target tp_klt
tp_klt_EXTERNAL_OBJECTS =

tp/tp_klt: tp/CMakeFiles/tp_klt.dir/tp_klt.cpp.o
tp/tp_klt: tp/CMakeFiles/tp_klt.dir/build.make
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_vs.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_tt_mi.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_tt.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_mbt.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_klt.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_robot.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_imgproc.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_gui.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_detection.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_ar.so.3.4.1
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.2.0
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_sensor.so.3.4.1
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libv4l2.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libv4lconvert.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libdc1394.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libSM.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libICE.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libX11.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libXext.so
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_vision.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_visual_features.so.3.4.1
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.2.0
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_me.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_blob.so.3.4.1
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_io.so.3.4.1
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libjpeg.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libpng.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.2.0
tp/tp_klt: /home/thomas/visp-ws/visp-build/lib/libvisp_core.so.3.4.1
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/liblapack.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libblas.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libxml2.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libpthread.so
tp/tp_klt: /usr/lib/gcc/x86_64-linux-gnu/9/libgomp.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libpthread.so
tp/tp_klt: /usr/lib/gcc/x86_64-linux-gnu/9/libgomp.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libz.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libzbar.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.2.0
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libm.so
tp/tp_klt: /usr/lib/x86_64-linux-gnu/libnsl.so
tp/tp_klt: tp/CMakeFiles/tp_klt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas/Documents/VROB1/VROB-code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tp_klt"
	cd /home/thomas/Documents/VROB1/VROB-code/tp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp_klt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tp/CMakeFiles/tp_klt.dir/build: tp/tp_klt

.PHONY : tp/CMakeFiles/tp_klt.dir/build

tp/CMakeFiles/tp_klt.dir/clean:
	cd /home/thomas/Documents/VROB1/VROB-code/tp && $(CMAKE_COMMAND) -P CMakeFiles/tp_klt.dir/cmake_clean.cmake
.PHONY : tp/CMakeFiles/tp_klt.dir/clean

tp/CMakeFiles/tp_klt.dir/depend:
	cd /home/thomas/Documents/VROB1/VROB-code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/Documents/VROB1/VROB-code /home/thomas/Documents/VROB1/VROB-code/tp /home/thomas/Documents/VROB1/VROB-code /home/thomas/Documents/VROB1/VROB-code/tp /home/thomas/Documents/VROB1/VROB-code/tp/CMakeFiles/tp_klt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tp/CMakeFiles/tp_klt.dir/depend

