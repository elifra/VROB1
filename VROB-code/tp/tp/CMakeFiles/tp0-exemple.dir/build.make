# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp"

# Include any dependencies generated for this target.
include tp/CMakeFiles/tp0-exemple.dir/depend.make

# Include the progress variables for this target.
include tp/CMakeFiles/tp0-exemple.dir/progress.make

# Include the compile flags for this target's objects.
include tp/CMakeFiles/tp0-exemple.dir/flags.make

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o: tp/CMakeFiles/tp0-exemple.dir/flags.make
tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o: tp0-exemple.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o"
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o -c "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp0-exemple.cpp"

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.i"
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp0-exemple.cpp" > CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.i

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.s"
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp0-exemple.cpp" -o CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.s

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.requires:
.PHONY : tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.requires

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.provides: tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.requires
	$(MAKE) -f tp/CMakeFiles/tp0-exemple.dir/build.make tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.provides.build
.PHONY : tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.provides

tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.provides.build: tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o

# Object files for target tp0-exemple
tp0__exemple_OBJECTS = \
"CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o"

# External object files for target tp0-exemple
tp0__exemple_EXTERNAL_OBJECTS =

tp/tp0-exemple: tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o
tp/tp0-exemple: tp/CMakeFiles/tp0-exemple.dir/build.make
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_vs.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_visual_features.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_vision.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_tt_mi.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_tt.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_me.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_mbt.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_klt.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_blob.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_sensor.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_robot.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_io.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_imgproc.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_gui.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_detection.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_core.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_ar.so.3.3.0
tp/tp0-exemple: /usr/local/lib/libopencv_video.so.3.1.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_sensor.so.3.3.0
tp/tp0-exemple: /usr/lib64/libv4l2.so
tp/tp0-exemple: /usr/lib64/libv4lconvert.so
tp/tp0-exemple: /usr/lib64/libdc1394.so
tp/tp0-exemple: /usr/lib64/libSM.so
tp/tp0-exemple: /usr/lib64/libICE.so
tp/tp0-exemple: /usr/lib64/libX11.so
tp/tp0-exemple: /usr/lib64/libXext.so
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_vision.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_visual_features.so.3.3.0
tp/tp0-exemple: /usr/local/lib/libopencv_xfeatures2d.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_flann.so.3.1.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_me.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_blob.so.3.3.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_io.so.3.3.0
tp/tp0-exemple: /usr/lib64/libjpeg.so
tp/tp0-exemple: /usr/lib64/libpng.so
tp/tp0-exemple: /usr/local/lib/libopencv_videoio.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
tp/tp0-exemple: /private/student/5/35/18007735/Documents/ESIR\ 2/BINP/visp_build/lib/libvisp_core.so.3.3.0
tp/tp0-exemple: /usr/local/lib/libopencv_core.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_imgproc.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_highgui.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_calib3d.so.3.1.0
tp/tp0-exemple: /usr/local/lib/libopencv_features2d.so.3.1.0
tp/tp0-exemple: /usr/lib64/liblapack.so
tp/tp0-exemple: /usr/lib64/libblas.so
tp/tp0-exemple: /usr/lib64/libxml2.so
tp/tp0-exemple: /usr/lib64/libpthread.so
tp/tp0-exemple: /usr/lib64/libz.so
tp/tp0-exemple: /usr/local/lib/libopencv_objdetect.so.3.1.0
tp/tp0-exemple: /usr/lib64/libm.so
tp/tp0-exemple: /usr/lib64/libnsl.so
tp/tp0-exemple: tp/CMakeFiles/tp0-exemple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tp0-exemple"
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp0-exemple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tp/CMakeFiles/tp0-exemple.dir/build: tp/tp0-exemple
.PHONY : tp/CMakeFiles/tp0-exemple.dir/build

tp/CMakeFiles/tp0-exemple.dir/requires: tp/CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o.requires
.PHONY : tp/CMakeFiles/tp0-exemple.dir/requires

tp/CMakeFiles/tp0-exemple.dir/clean:
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" && $(CMAKE_COMMAND) -P CMakeFiles/tp0-exemple.dir/cmake_clean.cmake
.PHONY : tp/CMakeFiles/tp0-exemple.dir/clean

tp/CMakeFiles/tp0-exemple.dir/depend:
	cd "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code" "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp" "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp" "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp" "/private/student/5/35/18007735/Documents/ESIR 2/BINP/TP/tp_binp/BINP/BINP-code/tp/tp/CMakeFiles/tp0-exemple.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tp/CMakeFiles/tp0-exemple.dir/depend

