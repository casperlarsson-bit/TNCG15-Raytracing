# TNCG15 Project - Ray tracing from scratch in C++

A Monte Carlo Ray Tracer implemented from scratch in C++ in the course TNCG15 - Advanced Global Illumination and Rendering.

## Ray tracer description

This is a traditional ray tracer implemented for a small hexagonal room with walls and one lamp in the ceiling. The walls, floor and ceiling consist of triangles and rectangles implemented as two different classes. Supported objects in the scene are spheres, cubes and tetrahedrons, with either Lambertian surface, glass or mirror material. The objects can either consist of one colour, or textures from a desired file.

## Folder structure

```
.
├── include             # Header files
├── src                 # Cpp files
├── images              # Images from the ray tracer
├── textures            # Texture files
├── CMakeLists.txt      # Configureation for CMake creation
└── README.md
```

## Setup instructions

Dependencies:

- [CMake](https://cmake.org/download/) for cross-platform compiler project generation.
- C++17 Required, e.g. [Visual Studio](https://visualstudio.microsoft.com/downloads/)

1. git clone https://github.com/casperlarsson-bit/Raytracing-TNCG15.git
1. Open CMake, enter the source path and the preferred build directory ("bin" folder) and hit configure.
1. Hit Generate and then Open Project to open the project in your IDE.
1. Update the CMakeLists.txt file when new .cpp or .h files are added.

<img src="images/Raytracing.png" alt="Raytracer" />

Convert .PMM image to .PNG on [Convertio](https://convertio.co/)
