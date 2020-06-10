cmake_minimum_required(VERSION 3.16)
project(Kursach)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
add_executable(Kursach
        main.cpp
        Matrix.cpp
        Matrix.h)
