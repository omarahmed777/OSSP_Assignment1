cmake_minimum_required(VERSION 3.23)
project(OSSP_Assignment1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(OSSP_Assignment1
        bst.c
        bst.h
        test_bst.c)
