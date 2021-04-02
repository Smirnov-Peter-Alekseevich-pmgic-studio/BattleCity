cmake_minimum_required(VERSION 3.20 FATAL_ERROR) 	# minimal version of cmake

set(PROJECT_NAME BattleCity)						#project name

project (${PROJECT_NAME})							 	#set project name

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

target_link_libraries(${PROJECT_NAME} glfw)