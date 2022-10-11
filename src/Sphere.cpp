#include "../include/Sphere.h"
#include <iostream>

// Default constructor
Sphere::Sphere() {
	radius = 1.0;
	centreVertex = glm::vec4(0, 0, 0, 1);
	color = ColorDBL();
	material = Material::LAMBERTIAN;
}

// Value constructor
Sphere::Sphere(double _radius, glm::vec4 _centreVertex, ColorDBL _color, Material _material) {
	radius = _radius;
	centreVertex = _centreVertex;
	color = _color;
	material = _material;
}

// Calculate the intersection of a ray and the surface
// Return the vertex where it hits
// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
glm::vec4 Sphere::rayIntersection(Ray& ray) const {
	glm::vec4 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = ray.getDirection();

	// Get parameters for quadratic equation
	double c1 = glm::dot(rayDirection, rayDirection);
	double c2 = 2.0f * glm::dot(rayDirection, glm::vec3(rayStart - centreVertex));
	double c3 = glm::dot(rayStart - centreVertex, rayStart - centreVertex) - radius * radius;

	// Arg is the value under square root
	double arg = c2 * c2 - 4.0 * c1 * c3;

	// Ray misses Sphere or just about hits it
	if (arg < COMPARE_ELLIPSE) return glm::vec4(NULL, NULL, NULL, NULL);

	// Time parameter for ray intersection, store only the lowest one
	double t = (-c2 - glm::sqrt(arg)) / (2 * c1);

	// ray.setColor(color);
	return rayStart + (float)t * glm::vec4(rayDirection, 1);
}

// Get what material the Sphere is made of
Material Sphere::getMaterial() const {
	return material;
}

// Sets the material of the Sphere
void Sphere::setMaterial(Material _material) {
	material = _material;
}

// Get the colour of the Sphere
ColorDBL Sphere::getColor() const {
	return color;
}

// Set the colour of the Sphere
void Sphere::setColor(ColorDBL _color) {
	color = _color;
}

// Get the centre of the sphere
glm::vec4 Sphere::getCentre() const {
	return centreVertex;
}