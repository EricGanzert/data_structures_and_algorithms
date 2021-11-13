add_library(calendar_utils STATIC
    api/calendar_utils.h
    src/calendar_utils.cpp
)

target_include_directories(calendar_utils
    PUBLIC    
        api
)

# unit tests
# add_executable(test_calendar_utils test_calendar_utils.cpp)

# target_link_libraries(test_calendar_utils
#     PUBLIC
#         gmock
#         calendar
# )