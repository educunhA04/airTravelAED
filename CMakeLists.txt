cmake_minimum_required(VERSION 3.22.1)
project(AirtravelAED)

set(CMAKE_CXX_STANDARD 17)

add_executable(AirtravelAED main.cpp
        Classes/Graph.h
        Classes/airport.h
        Classes/airlines.h
        Classes/airport.cpp
        Classes/airlines.cpp
        Classes/read.cpp
        Classes/read.h
        Classes/read.cpp
        Classes/menu.cpp
        Classes/menu.h
)
