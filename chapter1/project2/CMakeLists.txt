add_library(calendar STATIC
    calendar.h
    calendar.cpp
)

target_link_libraries(calendar
    PRIVATE
        calendar_utils
)

# unit tests
add_executable(test_calendar test_calendar.cpp)

target_link_libraries(test_calendar
    PUBLIC
        gmock
        calendar
        calendar_utils
)

add_subdirectory(calendar_utils)