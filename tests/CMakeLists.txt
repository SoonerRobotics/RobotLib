add_executable(tests 
    util_tests.cpp
)

target_link_libraries(tests catch)
target_link_libraries(tests RobotLib)

add_test(Tests tests)