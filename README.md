# Basic-Engine

A lightweight and straightforward 3D rendering engine built from the ground up using C++ and OpenGL. This project serves as a foundational exploration into the core concepts of computer graphics.

## Features

*   **Window and Input Management:** Utilizes GLFW for creating windows and handling user input.
*   **3D Rendering:** Implements a basic rendering pipeline with shaders, vertex buffers, and index buffers.
*   **Camera System:** A simple camera for navigating the 3D scene.
*   **Texture Loading:** Supports loading and applying textures to objects.

## Getting Started

### Prerequisites

*   A C++ compiler (MSVC, GCC, Clang)
*   CMake (version 3.10 or later)

### Dependencies

The following dependencies are included or managed by CMake:

*   [OpenGL](https://www.opengl.org/)
*   [GLFW](https://www.glfw.org/)
*   [GLM](https://glm.g-truc.net/0.9.9/index.html)
*   [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

### Building

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/Basic-Engine.git
    cd Basic-Engine
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure with CMake:**
    ```bash
    cmake ..
    ```

4.  **Build the project:**
    ```bash
    cmake --build .
    ```

## Project Structure

```
.
├── Engine/         # Core engine components
├── src/            # Main application source
├── textures/       # Texture files
├── cmake/          # CMake helper scripts
├── CMakeLists.txt  # Main CMake build file
└── README.md
```
