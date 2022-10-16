#include "../include/Ray.h"
#include <iostream>

// Default constructor
Ray::Ray() {
	startVertice = glm::vec3(-1.0f, 0.0f, 0.0f); // Eye position

	direction = glm::vec3(1.0f, 0.0f, 0.0f);
	endVertice = startVertice + direction;
	prevRay = nullptr;
	nextRay = nullptr;

	Polygon* newPolygon{};
	rayPolygonIntersection = newPolygon;
	rayType = RayType::PRIMARY;

	objectMaterial = Material::LAMBERTIAN;
	objectNormal = glm::vec3(1.0f, 0.0f, 0.0f);
}

// Constructor which sets starting position and direction
Ray::Ray(glm::vec3 _startPosition, glm::vec3 _direction, RayType _rayType) {
	startVertice = _startPosition;
	direction = _direction;

	endVertice = _startPosition + _direction;
	rayColor = ColorDBL();

	prevRay = nullptr;
	nextRay = nullptr;

	Polygon* newPolygon{};
	rayPolygonIntersection = newPolygon;
	rayType = _rayType;

	objectMaterial = Material::LAMBERTIAN;
	objectNormal = glm::vec3(1.0f, 0.0f, 0.0f);
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

// Set the Color of the ray with floats
void Ray::setColor(float _r, float _g, float _b) {
	rayColor = ColorDBL(_r, _g, _b);
}

// Set the direction of a Ray
void Ray::setDirection(glm::vec3 _direction) {
	direction = _direction;
}

// Set the end vertex of the ray
void Ray::setEndVertex(glm::vec3 _endVertex) {
	endVertice = _endVertex;
}

// Set the normal of the object the ray intersected with
void Ray::setObjectNormal(glm::vec3 _normal) {
	objectNormal = _normal;
}

// Set the material of the object the ray intersected with
void Ray::setObjectMaterial(Material _material) {
	objectMaterial = _material;
}

// Get the normal of the object the ray intersected with
glm::vec3 Ray::getObjectNormal() const {
	return objectNormal;
}

// Get the material of the object the ray intersected with
Material Ray::getObjectMaterial() const {
	return objectMaterial;
}

// Get startpoint of Ray
glm::vec3 Ray::getStartpoint() const {
	return startVertice;
}

// Get endpoint of Ray
glm::vec3 Ray::getEndpoint() const {
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