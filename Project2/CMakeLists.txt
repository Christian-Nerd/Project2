cmake_minimum_required(VERSION 3.26)
project(Project2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $(../))
set(WORKING_DIRECTORY ../)
include_directories(.)

add_executable(Project2
        Account.h
        AccountClient.cpp
        AccountDriver.cpp)
