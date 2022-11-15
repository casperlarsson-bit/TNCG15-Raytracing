/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include "glm/glm.hpp"
#include "quadratic/quartic.h"
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"

class Torus {
public:
    // Default constructor
    Torus();

    // Value constructor
    Torus();

    // Calculate the intersection of a ray and the surface
    // Return true if hits the surface
    bool rayIntersection(Ray& ray, float& minDistance) const;

    // Get what material the Torus is made of
    Material getMaterial() const;

    // Sets the material of the Torus
    void setMaterial(Material _material);

    // Get the colour of the Torus
    ColorDBL getColor() const;

    // Set the colour of the Torus
    void setColor(ColorDBL _color);

    // Calculate the normal of the Torus at point P
    glm::vec3 getNormal(glm::vec3 p) const;

private:
    float innerRadius;
    float outerRadius;
    ColorDBL color;
    Material material;
};