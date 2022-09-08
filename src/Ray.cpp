#include "../include/Ray.h"
#include <iostream>

// Default constructor
Ray::Ray() {
	startVertice = glm::vec4(-1, 0, 0, 1); // Eye position
}

// Destructor
Ray::~Ray() = default;

//// Class Member Functions

// Get the current Color of the ray
ColorDBL Ray::getColor() {
	return this->rayColor;
}

// Set the Color of the ray
void Ray::setColor(ColorDBL _rgb) {
	rayColor = _rgb;
}

// Set the Color of the ray with doubles
void Ray::setColor(double _r, double _g, double _b) {
	rayColor = ColorDBL(_r, _g, _b);
}

// Get startpoint of Ray
glm::vec4 Ray::getStartpoint() {
	return startVertice;
}

// Get endpoint of Ray
glm::vec4 Ray::getEndpoint() {
	return endVertice;
}

// Get direction of Ray
glm::vec3 Ray::getDirection() {
	return direction;
}