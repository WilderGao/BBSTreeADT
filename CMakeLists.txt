cmake_minimum_required(VERSION 3.8)
project(BBSTree)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp BBSTree.h BBSTree.cpp)
add_executable(BBSTree ${SOURCE_FILES})