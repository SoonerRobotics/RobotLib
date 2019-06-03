cmake_minimum_required(VERSION 3.5.1)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
set (CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

project (RobotLib)
enable_testing()

add_subdirectory (arduino)
add_subdirectory (src)
add_subdirectory (catchlib)
add_subdirectory (tests)