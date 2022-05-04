set(_glfw3_HEADER_SEARCH_DIRS
"C:/Dev/Basic-Engine/OpenGL/include/GLFW"
)

set(_glfw3_LIB_SEARCH_DIRS
"${CMAKE_SOURCE_DIR}/OpenGL/lib"
)

# Check environment for root search directory
set(_glfw3_ENV_ROOT $ENV{GLFW3_ROOT})
if(NOT GLFW3_ROOT AND _glfw3_ENV_ROOT)
  set(GLFW3_ROOT ${_glfw3_ENV_ROOT})
endif()

# Put user specified location at the beginning of search
if(GLFW3_ROOT)
  list(INSERT _glfw3_HEADER_SEARCH_DIRS 0 "${GLFW3_ROOT}/include")
  list(iNSERT _glfw3_LIB_SEARCH_DIRS 0 "${GLFW3_ROOT}/lib")
endif()

# Search for the header
find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h"
          paths ${_glfw3_HEADER_SEARCH_DIRS})

# Search for the library
find_library(GLFW3_LIBRARY names glfw3 glfw
            paths ${_glfw3_LIB_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glfw3 DEFAULT_MSG GLFW3_LIBRARY GLFW3_INCLUDE_DIR)