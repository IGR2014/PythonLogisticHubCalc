cmake_minimum_required(
	VERSION
	3.15
)


set(
	CMAKE_BUILD_TYPE
	Release
)


project(test)


add_executable(
	golden_selection
	golden_selection.cpp
)

install(
	TARGETS golden_selection
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/install"
)


add_executable(
	ternary_search
	ternary_search.cpp
)

install(
	TARGETS ternary_search
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/install"
)


add_executable(
	coordinate_descent
	coordinate_descent.cpp
)

install(
	TARGETS coordinate_descent
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/install"
)

