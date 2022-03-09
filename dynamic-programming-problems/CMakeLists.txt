add_library(dynamic-programming-problems STATIC
    dynamic_programming_problems.h
    dynamic_programming_problems.cpp
)

add_executable(test-dynamic-programming-problems test_dynamic_programming_problems.cpp)

target_link_libraries(test-dynamic-programming-problems
    PUBLIC
        gmock
        dynamic-programming-problems
)