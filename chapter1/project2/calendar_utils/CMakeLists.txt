add_library(calendar_utils STATIC
    api/calendar_utils.h
    src/calendar_utils.cpp
)

target_include_directories(calendar_utils
    PUBLIC    
        api
)

add_subdirectory(test)
