file(GLOB SOURCES
    *.h
    *.cpp
)

add_library(RobotLib ${SOURCES})
target_link_libraries (RobotLib arduino)

target_include_directories(RobotLib
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)