cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(matrix
        main.cpp
        CSRmatrix.h
        CSRmatrix.cpp)
