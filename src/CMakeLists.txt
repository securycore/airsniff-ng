cmake_minimum_required(VERSION 3.8)
project(airsniff-ng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lreadline -lpcap")
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp color.h)
add_executable(airsniff-ng ${SOURCE_FILES})
