add_executable(test_calendar_utils test_calendar_utils.cpp)

target_link_libraries(test_calendar_utils
    PUBLIC
        calendar_utils
        gmock
)