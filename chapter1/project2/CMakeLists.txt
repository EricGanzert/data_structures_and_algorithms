add_library(calendar STATIC
    calendar.h
    calendar.cpp
)

# unit tests
add_executable(test_calendar test_calendar.cpp)

target_link_libraries(test_calendar
    PUBLIC
        gmock
        calendar
)