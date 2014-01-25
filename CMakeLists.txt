project(URG2OSG)
cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SRC_LIST src/* URG2OSG/* main.cpp)
include_directories(.)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} urg_cpp m osg osgViewer boost_system)
