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
        gmock
        chapter1
        steady_clock
)

add_library(steady_clock STATIC
    steady_clock.h
    steady_clock.cpp
)

add_executable(test_chapter1_project1 test_chapter1_project1.cpp)

target_link_libraries(test_chapter1_project1
    PUBLIC
        gmock
        chapter1
)