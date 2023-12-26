cmake_minimum_required(VERSION 3.27)
project(AirtravelAED)

set(CMAKE_CXX_STANDARD 17)

add_executable(AirtravelAED main.cpp
        main.cpp
        Classes/Graph.h
        Classes/airport.h
        Classes/airlines.h
        Classes/airport.cpp
        Classes/airlines.cpp
)
