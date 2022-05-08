cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
	CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS}\
	-Wall\
	-Wextra\
	-Wpedantic\
	-Wshadow\
	-Wundef\
	-Wno-missing-field-initializers"
)

set(PROJECT_NAME "hinkeller")

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

project (${PROJECT_NAME})

set(
    SRC_DIR
        ${CMAKE_CURRENT_LIST_DIR}/src
)

set(
    INC_DIR
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

set(
    SRC_LIST
        ${SRC_DIR}/Background.cpp
        ${SRC_DIR}/Character.cpp
        ${SRC_DIR}/FallingObject.cpp
        ${SRC_DIR}/loadTextures.cpp
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Score.cpp
        ${SRC_DIR}/Text.cpp
        ${SRC_DIR}/Utils.cpp
)

find_package(SFML 2 COMPONENTS audio graphics window system)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	message("\nSFML directory not found.")
endif()

add_executable(
	${PROJECT_NAME}
	${SRC_LIST}
)

target_sources(
    ${PROJECT_NAME} PRIVATE
	${SRC_LIST}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
        ${INC_DIR}
)

target_link_libraries(
	${PROJECT_NAME}
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME
	DESTINATION
	${ROOT_DIR}
)
