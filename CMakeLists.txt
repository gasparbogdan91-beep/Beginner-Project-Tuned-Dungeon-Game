cmake_minimum_required(VERSION 4.1)
project(project1)

set(CMAKE_CXX_STANDARD 23)

add_executable(1 main.cpp
        Player.cpp
        Player.h
        Config.h
        Monster.cpp
        Monster.h
        RollRNG.h)

target_compile_options(1 PRIVATE -Wall -Wextra)