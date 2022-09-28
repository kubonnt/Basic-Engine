# It does not work atm
cmake_minimum_required(VERSION 3.1)

project(Engine)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/*.cpp
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/src/*.cpp
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/src/*.c)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/include/*.h)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/OpenGL/lib)

# Configure assets header file
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

# Define executables
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Code to find external libs
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/Dev/Basic-Engine/cmake")

# OpenGL
find_package(OpenGL REQUIRED)
# GLM
find_package(glm REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
# GLFW
find_package(glfw3 REQUIRED)
message(STATUS "GLFW included at ${GLFW3_INCLUDE_DIR}")
# ASSIMP tbd

# Header only libraries
# STB_IMAGE
add_library(stb_image "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/src/ext/stb_image.cpp")
# GLAD
add_library(glad "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/src/ext/glad.c")
#set_target_properties(glad PROPERTIES LINKER_LANGUAGE CXX)

set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glad ${CMAKE_DL_LIBS} stb_image)

# Define include DIRs
include_directories(
        "${CMAKE_SOURCE_DIR}/OpenGL/include/glad"
        "${CMAKE_SOURCE_DIR}/OpenGL/include/glm"
        "${CMAKE_SOURCE_DIR}/OpenGL/include/"
)

# Define link libs
target_link_libraries(${PROJECT_NAME} ${LIBS})

if(MSVC_IDE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} files ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()





