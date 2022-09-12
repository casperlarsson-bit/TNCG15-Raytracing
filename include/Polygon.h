#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Ray.h"

class Polygon {
public:

	// Default constructor
	Polygon();

	// Compute the normal of the Polygon. Normal points into the room
	glm::vec3 getNormal() const;

	// Calculate the normal automatically from the vertices
	virtual void calculateNormal() = 0;

	// Get the colour of the Polygon
	ColorDBL getColor() const;

	// Set the colour of the Polygon
	void setColor(ColorDBL _color);

	// Calculate the intersection of a ray and the surface
	// Return the vertex where it hits
	// Done in sub classes
	virtual glm::vec4 rayIntersection(Ray &ray) const = 0;

	ColorDBL color;
	glm::vec3 normal;
private:
};