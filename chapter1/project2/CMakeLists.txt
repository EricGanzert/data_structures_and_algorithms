add_library(calendar STATIC
    api/calendar.h
    api/calendar_utils.h
    src/calendar.cpp
    src/calendar_utils.cpp
)

target_include_directories(calendar
    PUBLIC
        api
)

add_executable(calendar_month main.cpp)

target_link_libraries(calendar_month
    PUBLIC
        calendar
)

# unit tests
add_executable(test_calendar test_calendar.cpp)

target_link_libraries(test_calendar
    PUBLIC
        gmock
        calendar
)
