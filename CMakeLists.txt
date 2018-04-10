cmake_minimum_required(VERSION 3.10)

set(NAME ft_vox)

project(${NAME} CXX)

set(CMAKE_CPP_STANDARD 11)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glew/build/cmake)

add_executable(${NAME} srcs/main.cpp srcs/Core.cpp srcs/Core.hpp)

target_include_directories(${NAME} PUBLIC ${OPENGL_INCLUDE_DIR} deps/glfw/include deps/glew/include)
target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY} glfw glew)
