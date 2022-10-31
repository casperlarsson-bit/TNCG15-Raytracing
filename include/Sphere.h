/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"
#include "Polygon.h"

class Sphere {
public:
	// Default constructor
	Sphere();

	// Value constructor
	Sphere(float _radius, glm::vec3 _centreVertex, ColorDBL _color, Material _material);

	// Calculate the intersection of a ray and the surface
	// Return true if hits the surface
	// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
	bool rayIntersection(Ray& ray, float& minDistance) const;

	// Get what material the Sphere is made of
	Material getMaterial() const;

	// Sets the material of the Sphere
	void setMaterial(Material _material);

	// Get the colour of the Sphere
	ColorDBL getColor() const;

	// Set the colour of the Sphere
	void setColor(ColorDBL _color);

	// Get the centre of the sphere
	glm::vec3 getCentre() const;

private:
	float radius;
	glm::vec3 centreVertex;
	ColorDBL color;
	Material material;
};