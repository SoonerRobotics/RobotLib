add_library(catch
	catch.hpp
	catch.cpp
)

target_include_directories(catch
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)