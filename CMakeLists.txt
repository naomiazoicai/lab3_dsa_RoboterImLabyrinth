cmake_minimum_required(VERSION 3.24)
project(lab3_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab3_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Queue.cpp
        Queue.h
        ShortTest.cpp
        ShortTest.h Stack.h Stack.cpp ShortTestStack.h ShortTestStack.cpp Labyrinth.cpp Labyrinth.h)
