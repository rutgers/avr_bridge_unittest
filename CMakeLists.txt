cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


set(AVR_BRIDGE_CONFIG unittest.yaml)
set(ARDUINO_TYPE "arduino_diecimila")
rosbuild_find_ros_package(avr_bridge)
include(${avr_bridge_PACKAGE_PATH}/arduino_cmake/avrbuild.cmake)


set(PROJECT_SRC src/main.cpp src/avr_ros_user.cpp)

add_executable(firmware ${PROJECT_SRC} ${AVR_ROS_SRC} ${ARDUINO_SRC})
add_dependencies(firmware gen_avr_ros)
