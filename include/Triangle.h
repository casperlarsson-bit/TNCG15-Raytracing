#pragma once
#include "Polygon.h"


class Triangle : public Polygon {
public:

	// Set the vertices of the Triangle
	void setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2);
private:
	glm::vec4 v0, v1, v2;
};