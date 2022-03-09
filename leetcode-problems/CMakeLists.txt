add_library(leetcode-problems STATIC
    leetcode_problems.h
    leetcode_problems.cpp
)

add_executable(test-leetcode-problems test_leetcode_problems.cpp)

target_link_libraries(test-leetcode-problems
    PUBLIC
        gmock
        leetcode-problems
)