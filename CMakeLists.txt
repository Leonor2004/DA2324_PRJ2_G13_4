cmake_minimum_required(VERSION 3.26)
project(DA2324_PRJ2_G13_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA2324_PRJ2_G13_4
        AuxFunctions.h
        AuxFunctions.cpp
        main.cpp
        csvInfo.cpp
        csvInfo.cpp
        Graph.cpp
        Graph.h
        TSP.cpp
        TSP.h)
