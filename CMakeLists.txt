cmake_minimum_required(VERSION 3.10)
project(Agenda)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/include)

file(GLOB SOURCES
    src/main.cpp
    src/core/*.cpp
)

add_executable(agenda ${SOURCES})
