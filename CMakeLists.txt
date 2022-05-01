cmake_minimum_required(VERSION 3.4)

project (
    Matrix
    VERSION 0.0.1
    DESCRIPTION "Source code for the Matrix programming language"
)

add_compile_options(-std=c++20)

file(GLOB_RECURSE SRCFILES "src/*.cpp")

add_executable(matrix ${SRCFILES} "main.cpp")
