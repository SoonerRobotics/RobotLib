add_executable(tests 
    util_tests.cpp
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src
                     )

target_link_libraries(tests catch)
target_link_libraries(tests RobotLib)