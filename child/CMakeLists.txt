cmake_minimum_required(VERSION 3.1)

project(child)

set(CMAKE_CXX_STANDARD 11)
set(SOURCES main.cpp)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(child ${SOURCES})