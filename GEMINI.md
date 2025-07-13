# Gemini Project Information

## Project Overview

- **Project Name:** Basic-Engine
- **Language:** C++
- **Build System:** CMake
- **Description:** A basic 3D rendering engine.

## Dependencies

- **OpenGL:** Graphics API
- **GLFW:** Windowing and input library
- **GLM:** Mathematics library

## Directory Structure

- `src/`: Main source code
- `Engine/`: Engine-specific code
- `cmake/`: CMake modules
- `textures/`: Image textures
- `OpenGL/`: OpenGL headers and libraries
- `glfw-3.3.5/`: GLFW source code

## Building

The project is built using CMake. The main `CMakeLists.txt` is in the root directory.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
