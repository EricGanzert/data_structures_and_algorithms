add_library(chapter2 STATIC
    chapter2.h
    chapter2.cpp
)

add_executable(test_chapter2 test_chapter2.cpp)

target_link_libraries(test_chapter2
    PUBLIC
        gmock
        chapter2
)