file(GLOB SOURCES
    *.cpp
    ../src/*.cpp
)

add_executable(tests ${SOURCES})

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(tests catch)
target_link_libraries(tests RobotLib)