add_library(chapter1 STATIC
    chapter1.h
    chapter1.cpp
)

target_link_libraries(chapter1
    PUBLIC
        steady_clock
)

add_executable(test_chapter1 test_chapter1.cpp)

target_link_libraries(test_chapter1
    PUBLIC
        gtest
        chapter1
        steady_clock
)

add_library(steady_clock STATIC
    steady_clock.h
    steady_clock.cpp
)

# add_library(mock_steady_clock STATIC
#     mock_steady_clock.h    
# )