project(URG2OSG)
cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SRC_LIST src/* URG2OSG/*)
include_directories(.)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra")

add_executable(scanline_rt ${SRC_LIST}  main_scanline.cpp)
add_executable(scan3d ${SRC_LIST} main_scan3d.cpp)

target_link_libraries(scanline_rt urg_cpp m osg osgViewer boost_system dxl boost_timer pcl_io pcl_common)
target_link_libraries(scan3d urg_cpp m osg osgViewer boost_system dxl boost_timer pcl_io pcl_common)
