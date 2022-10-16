#pragma once
#include "Polygon.h"


class Rectangle : public Polygon {
public:
	// Default constructor
	Rectangle();

	// Calculate the normal automatically from the vertices
	void calculateNormal();

	// Set the vertices of the Rectangle
	void setVertices(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3);

	// Calculate the intersection of a ray and the surface
	// Return true if hits the surface
	bool rayIntersection(Ray& ray, float& minDistance) const;

	glm::vec3 v0, v1, v2, v3;
private:
};