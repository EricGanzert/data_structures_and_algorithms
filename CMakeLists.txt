cmake_minimum_required(VERSION 3.16)
project(data_structures_and_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(chapter1)
add_subdirectory(lib/googletest)