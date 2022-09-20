#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"
#include "Triangle.h"

class Tetrahedron {
public:
	// Default constructor
	Tetrahedron();

	// Value constructor
	Tetrahedron(glm::vec4 v0, glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, ColorDBL _color, Material _material);

	// Calculate the intersection of a ray and the surface
	// Return the vertex where it hits
	// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
	glm::vec4 rayIntersection(Ray& ray) const;

	// Get what material the Tetrahedron is made of
	Material getMaterial() const;

	// Sets the material of the Tetrahedron
	void setMaterial(Material _material);

	// Get the colour of the Tetrahedron
	ColorDBL getColor() const;

	// Set the colour of the Tetrahedron
	void setColor(ColorDBL _color);

	
private:
	ColorDBL color;
	Material material;
	glm::vec4 vertexTable[4]; // Vertices to build triangles
	Triangle triangleTable[4]; // Triangles to store the surfaces
};