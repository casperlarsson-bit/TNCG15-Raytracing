#pragma once
#include "glm/glm.hpp"
#inculde "ColorDBL.h"

class Polygon {
public:

	// Default constructor
	Polygon();


	// Compute the normal of the Polygon. Normal points into the room
	glm::vec4 getNormal() const;

	// Get the colour of the Polygon
	ColorDBL getColor() const;

	// Set the colour of the Polygon
	void setColor(ColorDBL _color);
private:
	ColorDBL color;
	glm::vec4 normal;
};