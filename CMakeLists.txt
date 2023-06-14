cmake_minimum_required(VERSION 3.26)
project(OpenglRenderer)

set (CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(glm)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ./include glm stb_image/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw glad) 
