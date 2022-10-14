#pragma once
#include "Polygon.h"


class Triangle : public Polygon {
public:
	// Default constructor
	Triangle();

	// Calculate the normal automatically from the vertices
	void calculateNormal();

	// Set the vertices of the Triangle
	void setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2);

	// Calculate the intersection of a ray and the surface
	// Return true if hits the surface
	bool rayIntersection(Ray& ray, double& minDistance) const;
private:
	glm::vec4 v0, v1, v2;
};