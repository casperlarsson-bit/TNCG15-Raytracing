#pragma once
#include "Polygon.h"


class Triangle : public Polygon {
public:
	// Default constructor
	Triangle();

	// Set the vertices of the Triangle
	void setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2);

	// Calculate the intersection of a ray and the surface
	// Return the vertex where it hits
	glm::vec4 rayIntersection(Ray& ray) const;
private:
	glm::vec4 v0, v1, v2;
};