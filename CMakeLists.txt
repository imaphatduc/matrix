cmake_minimum_required(VERSION 3.4)

project (
    Matrix
    VERSION 0.0.1
    DESCRIPTION "The Matrix programming language"
)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_compile_options(-std=c++20)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB_RECURSE SRCFILES "src/*.cpp")

add_executable(matc ${SRCFILES} "main.cpp")

llvm_map_components_to_libnames(llvm_libs core irreader support target)

target_link_libraries(matc ${llvm_libs})
