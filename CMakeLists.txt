cmake_minimum_required(VERSION 3.4)

project (
    Matrix
    VERSION 0.0.1
    DESCRIPTION "The Matrix programming language"
)

add_compile_options(-std=c++20)

file(GLOB_RECURSE SRCFILES "src/*.cpp")

add_executable(matc ${SRCFILES} "main.cpp")
