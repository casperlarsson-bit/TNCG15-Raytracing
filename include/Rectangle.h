#pragma once
#include "Polygon.h"


class Rectangle : public Polygon {
public:
	// Default constructor
	Rectangle();

	// Calculate the normal automatically from the vertices
	void calculateNormal();

	// Set the vertices of the Rectangle
	void setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2, glm::vec4 _v3);

	// Calculate the intersection of a ray and the surface
	// Return the vertex where it hits
	glm::vec4 rayIntersection(Ray& ray) const;

	glm::vec4 v0, v1, v2, v3;
private:
};