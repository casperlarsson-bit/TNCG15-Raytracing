/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

# include "../include/Torus.h"

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
bool Torus::rayIntersection(Ray& ray, float& minDistance) const {
    return false;
}

// Get what material the Torus is made of
Material Torus::getMaterial() const {
    return material;
}

// Sets the material of the Torus
void Torus::setMaterial(Material _material) {
    material = _material;
}

// Get the colour of the Torus
ColorDBL Torus::getColor() const {
    return color;
}

// Set the colour of the Torus
void Torus::setColor(ColorDBL _color) {
    color = _color;
}