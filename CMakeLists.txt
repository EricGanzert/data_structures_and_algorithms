cmake_minimum_required(VERSION 3.16)
project(data_structures_and_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if(WIN32)
add_compile_options(
    "/W3"
    "/WX" # Turn on warnings as errors
)
endif()

add_subdirectory(lib/googletest)
add_subdirectory(chapter1)
add_subdirectory(chapter2)
add_subdirectory(chapter3)
add_subdirectory(leetcode-problems)
add_subdirectory(dynamic-programming-problems)
