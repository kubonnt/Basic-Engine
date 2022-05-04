set(_glm_HEADER_SEARCH_DIRS
"C:/Dev/Basic-Engine/OpenGL/include/glm"
)

# Check environment variable
set(_glm_ENV_ROOT_DIR $ENV{GLM_ROOT_DIR})
if(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)
  set(GLM_ROOT_DIR ${_glm_ENV_ROOT_DIR})
endif()

# Put user specified location at the beginning of the search
if(GLM_ROOT_DIR)
  set(_glm_HEADER_SEARCH_DIRS ${GLM_ROOT_DIR} "${GLM_ROOT_DIR}/include" ${_glm_HEADER_SEARCH_DIRS})
endif()

# Locate header 
find_path(GLM_INCLUDE_DIR names glm.hpp
          paths ${_glm_HEADER_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glm DEFAULT_MSG GLM_INCLUDE_DIR)

if(GLM_FOUND)
  set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
  message(STATUS "GLM_INCLUDE_DIR = ${GLM_INCLUDE_DIR}")
endif()
