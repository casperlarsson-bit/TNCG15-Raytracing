/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"
#include "Rectangle.h"
#include <string>

class Cube {
public:
    // Default construcot
    Cube();

    // Value constructor
    Cube(glm::vec3 _midVertex, float size, ColorDBL _color, Material _material);

    // Get what material the Cube is made of
    Material getMaterial() const;

    // Set the material of the Cube
    void setMaterial(Material _material);

    // Get the colour of the Cube
    ColorDBL getColor() const;

    // Set the colour of the Cube
    void setColor(ColorDBL _color);

    // Calculate the intersection of a ray and the surface
    void rayIntersection(Ray& ray, float& minDistance) const;

    Rectangle rectangleTable[6]; // Rectangles to store the surface
private:
    ColorDBL color;
    Material material;
    glm::vec3 vertexTable[8]; // Vertices to build rectangles
};