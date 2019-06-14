cmake_minimum_required(VERSION 3.5.1)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wpedantic -Wextra")

set (CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
set (CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
set (CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

project (RobotLib)

enable_testing()

add_subdirectory (arduino)
add_subdirectory (src)
add_subdirectory (catchlib)
add_subdirectory (tests)

add_test (NAME Test COMMAND tests)