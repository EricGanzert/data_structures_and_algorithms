add_library(chapter3 STATIC
    chapter3.h
    chapter3.cpp
)

add_executable(test_chapter3 test_chapter3.cpp)

target_link_libraries(test_chapter3
    PUBLIC
        gmock
        chapter3
)