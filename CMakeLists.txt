cmake_minimum_required(VERSION 3.10)

set(NAME ft_vox)

project(${NAME} CXX)

set(CMAKE_CPP_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_FILES
	srcs/main.cpp
	srcs/Core.cpp
	srcs/Core.hpp
	srcs/exceptions/VoxException.cpp
	srcs/exceptions/VoxException.hpp
	srcs/exceptions/glfw/GlfwException.cpp
	srcs/exceptions/glfw/GlfwException.hpp
	srcs/exceptions/glfw/GlfwInitException.cpp
	srcs/exceptions/glfw/GlfwInitException.hpp
	srcs/exceptions/glfw/GlfwWindowCreationException.cpp
	srcs/exceptions/glfw/GlfwWindowCreationException.hpp
	srcs/exceptions/glew/GlewException.cpp
	srcs/exceptions/glew/GlewException.hpp
	srcs/exceptions/glew/GlewInitException.cpp
	srcs/exceptions/glew/GlewInitException.hpp
	srcs/graphics/Display.cpp
	srcs/graphics/Display.hpp
)

find_package(OpenGL REQUIRED)
add_definitions(-DGLEW_STATIC)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glew/build/cmake)

include_directories(srcs/)
add_executable(${NAME} ${SOURCE_FILES})

target_include_directories(${NAME} PUBLIC ${OPENGL_INCLUDE_DIR} deps/glfw/include deps/glew/include)
target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY} glfw glew)

if (WIN32)
	add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_BINARY_DIR}/bin/glew32d.dll
		$<TARGET_FILE_DIR:${NAME}>
	)
endif (WIN32)
