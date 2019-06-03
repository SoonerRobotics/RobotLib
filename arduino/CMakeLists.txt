file(GLOB SOURCES
    *.h
    *.cpp
)

add_library(arduino ${SOURCES})

target_include_directories(arduino
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)