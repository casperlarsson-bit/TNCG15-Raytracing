cmake_minimum_required(VERSION 3.13.0...3.20)
project(TNCG15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Raytracing src/main.cpp src/Ray.cpp src/Camera.cpp src/Pixel.cpp src/ColorDBL.cpp src/Polygon.cpp src/Rectangle.cpp src/Triangle.cpp src/Scene.cpp src/Sphere.cpp src/Tetrahedron.cpp src/functions.cpp src/Cube.cpp
    include/Ray.h include/Camera.h include/Pixel.h include/ColorDBL.h include/Polygon.h include/Rectangle.h include/Triangle.h include/Scene.h include/Material.h include/Sphere.h include/Tetrahedron.h include/functions.h include/Cube.h)

enable_warnings(Raytracing)
