cmake_minimum_required(VERSION 3.9)
project(Convert3D)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(Convert3D src/SimpleObjReader.cpp src/STLWriter.cpp)

target_include_directories(Convert3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})