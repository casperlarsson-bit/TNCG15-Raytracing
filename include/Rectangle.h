#pragma once
#include "Polygon.h"


class Rectangle : public Polygon {
public:

	// Set the vertices of the Rectangle
	void setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2, glm::vec4 _v3);
private:
	glm::vec4 v0, v1, v2, v3;
};