cmake_minimum_required(VERSION 3.1)

project(Engine LANGUAGES CXX)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/main.cpp
        ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
         ${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/include/*.h)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/OpenGL/lib)

# Configure assets header file
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)

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
add_library(STB_IMAGE "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/src/ext/stb_image.cpp")
# GLAD
add_library(GLAD "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/src/ext/glad.c")

set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} STB_IMAGE GLAD)

# Define include DIRs
include_directories(
        "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/src/"
        "${CMAKE_SOURCE_DIR}/Engine/Basic-Engine/graphics/include/"
        "${CMAKE_SOURCE_DIR/OpenGL/include/glad}"
        "${CMAKE_SOURCE_DIR/OpenGL/include/glm}"
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
                                string(REPLACE "/" "/" groupname ${curdir})
                                string(REPLACE "src" "Source" groupname ${curdir})
                                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
                        endif()
                endforeach()
        endmacro()

        GroupSources(src)

endif()


if(WIN32)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/dlls"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()




