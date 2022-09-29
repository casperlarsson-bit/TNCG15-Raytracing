#include "../include/Ray.h"
#include <iostream>

// Default constructor
Ray::Ray() {
	startVertice = glm::vec4(-1, 0, 0, 1); // Eye position

	direction = glm::vec3(1, 0, 0);
	endVertice = startVertice + glm::vec4(direction, 1);
	prevRay = nullptr;
	nextRay = nullptr;

	Polygon* newPolygon{};
	rayPolygonIntersection = newPolygon;
	rayType = RayType::PRIMARY;
}

// Constructor which sets starting position and direction
Ray::Ray(glm::vec4 _startPosition, glm::vec3 _direction, RayType _rayType) {
	startVertice = _startPosition;
	direction = _direction;

	endVertice = _startPosition + glm::vec4(_direction, 1);
	rayColor = ColorDBL();

	prevRay = nullptr;
	nextRay = nullptr;

	Polygon* newPolygon{};
	rayPolygonIntersection = newPolygon;
	rayType = _rayType;
}

// Destructor
Ray::~Ray() = default;

//// Class Member Functions

// Get the current Color of the ray
ColorDBL Ray::getColor() const {
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

// Set the direction of a Ray
void Ray::setDirection(glm::vec3 _direction) {
	direction = _direction;
}

// Set the end vertex of the ray
void Ray::setEndVertex(glm::vec4 _endVertex) {
	endVertice = _endVertex;
}

// Get startpoint of Ray
glm::vec4 Ray::getStartpoint() const {
	return startVertice;
}

// Get endpoint of Ray
glm::vec4 Ray::getEndpoint() const {
	return endVertice;
}

// Get direction of Ray
glm::vec3 Ray::getDirection() const {
	return direction;
}

// Get the Polygon which the Ray intersected with
Polygon* Ray::getPolygon() const {
	return rayPolygonIntersection;
}

// Get the type of ray (shadow, primary etc.)
RayType Ray::getRayType() const {
	return rayType;
}