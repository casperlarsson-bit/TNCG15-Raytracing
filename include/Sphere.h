#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"

class Sphere {
public:
	// Default constructor
	Sphere();

	// Value constructor
	Sphere(double _radius, glm::vec4 _centreVertex, ColorDBL _color, Material _material);

	// Calculate the intersection of a ray and the surface
	// Return the vertex where it hits
	// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
	glm::vec4 rayIntersection(Ray& ray) const;

	// Get what material the Sphere is made of
	Material getMaterial() const;

	// Sets the material of the Sphere
	void setMaterial(Material _material);

	// Get the colour of the Sphere
	ColorDBL getColor() const;

	// Set the colour of the Sphere
	void setColor(ColorDBL _color);

	// Get the centre of the sphere
	glm::vec4 getCentre() const;

private:
	double radius;
	glm::vec4 centreVertex;
	ColorDBL color;
	Material material;
};