add_library(calendar STATIC
    api/calendar.h
    src/calendar.cpp
)

target_link_libraries(calendar
    PRIVATE
        calendar_utils
)

target_include_directories(calendar
    PUBLIC
        api
)

add_executable(calendar_month main.cpp)

target_link_libraries(calendar_month
    PUBLIC
        calendar
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