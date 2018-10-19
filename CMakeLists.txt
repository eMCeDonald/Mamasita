cmake_minimum_required(VERSION 3.12)
project(Funfel)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Funfel
        include/functions.h
        include/Sbox.h
        src/functions.cpp
        src/main.cpp include/round_shift_table.h)
