set(_glfw3_HEADER_SEARCH_DIRS
"${CMAKE_SOURCE_DIR}/glfw-3.3.5/include"
"${CMAKE_SOURCE_DIR}/OpenGL/include/GLFW"
)

set(_glfw3_LIB_SEARCH_DIRS
"${CMAKE_SOURCE_DIR}/glfw-3.3.5/src"
"${CMAKE_SOURCE_DIR}/OpenGL/lib"
)

# Check environment for root search directory
set(_glfw3_ENV_ROOT $ENV{GLFW3_ROOT})
if(NOT GLFW3_ROOT AND _glfw3_ENV_ROOT)
  set(GLFW3_ROOT ${_glfw3_ENV_ROOT})
endif()

# Put user specified location at the beginning of search
if(GLFW3_ROOT)
  set(_glfw3_HEADER_SEARCH_DIRS ${GLFW3_ROOT} "${GLFW3_ROOT}/" ${_glfw3_HEADER_SEARCH_DIRS})
  set(_glfw3_LIB_SEARCH_DIRS ${GLFW3_ROOT} "${GLFW3_ROOT}/" ${_glfw3_LIB_SEARCH_DIRS})
endif()

# Search for the header
find_path(GLFW3_INCLUDE_DIR "glfw3.h"
          paths ${_glfw3_HEADER_SEARCH_DIRS})

# Search for the library
find_library(GLFW3_LIBRARY "glfw3"
            paths ${_glfw3_LIB_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glfw3 DEFAULT_MSG GLFW3_LIBRARY GLFW3_INCLUDE_DIR)