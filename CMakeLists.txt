cmake_minimum_required(VERSION 3.26)
project(OpenglRenderer)

set (CMAKE_CXX_STANDARD 17)

add_compile_options(-g)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp
	${CMAKE_SOURCE_DIR}/glm/*.h
	${CMAKE_SOURCE_DIR}/glm/*.hpp
	${CMAKE_SOURCE_DIR}/stb_image/*.h
	${CMAKE_SOURCE_DIR}/stb_image/*.hpp
	${CMAKE_SOURCE_DIR}/assimp/*.h
	${CMAKE_SOURCE_DIR}/assimp/*.hpp)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(assimp)

#add_subdirectory(glm) #doesn't work
add_subdirectory(tinyobjloader)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ./include ./glm ./stb_image ./tinyobjloader ./assimp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw glad assimp) 
