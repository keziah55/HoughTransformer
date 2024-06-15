cmake_minimum_required(VERSION 3.18)
project(hough)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)
