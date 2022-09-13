#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Ray.h"
#include "Material.h"

const double compareEllipse = 0.00001;

class Polygon {
public:

	// Default constructor
	Polygon();

	// Value constructor
	Polygon(ColorDBL _color, glm::vec3 _normal, Material _material);

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

	// Get what material the Polygon is made of
	Material getMaterial() const;

	// Sets the material of the Polygon
	void setMaterial(Material _material);

	ColorDBL color;
	glm::vec3 normal;
private:
	Material material;
};