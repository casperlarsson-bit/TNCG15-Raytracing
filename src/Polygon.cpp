#include "../include/Polygon.h"

// Default constructor
Polygon::Polygon() {

}


// Compute the normal of the Polygon. Normal points into the room
glm::vec3 Polygon::getNormal() const {
	return glm::normalize(normal);
}

// Get the colour of the Polygon
ColorDBL Polygon::getColor() const {
	return color;
}

// Set the colour of the Polygon
void Polygon::setColor(ColorDBL _color) {
	color = _color;
}