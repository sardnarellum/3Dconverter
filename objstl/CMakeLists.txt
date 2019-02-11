cmake_minimum_required(VERSION 3.9)
project(3objstl)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Convert3D/include)

add_executable(objstl src/main.cpp)

target_link_libraries(objstl LINK_PUBLIC Convert3D)
