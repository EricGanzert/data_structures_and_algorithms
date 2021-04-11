add_library(chapter1 STATIC
    chapter1.h
    chapter1.cpp
)

add_executable(test_chapter1 test_chapter1.cpp)

target_link_libraries(test_chapter1
    PUBLIC
        gtest
        chapter1
)
