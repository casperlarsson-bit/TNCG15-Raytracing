#include "../include/Sphere.h"
#include <iostream>

// Default constructor
Sphere::Sphere() {
	radius = 1.0;
	centreVertex = glm::vec3(0, 0, 0);
	color = ColorDBL();
	material = Material::LAMBERTIAN;
}

// Value constructor
Sphere::Sphere(double _radius, glm::vec3 _centreVertex, ColorDBL _color, Material _material) {
	radius = _radius;
	centreVertex = _centreVertex;
	color = _color;
	material = _material;
}

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
bool Sphere::rayIntersection(Ray& ray, double& minDistance) const {
	glm::vec3 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 x_i; // Intersection point

	// Get parameters for quadratic equation
	double c1 = glm::dot(rayDirection, rayDirection);
	float c2 = 2.0f * glm::dot(rayDirection, rayStart - centreVertex);
	double c3 = glm::dot(rayStart - centreVertex, rayStart - centreVertex) - radius * radius;

	// Arg is the value under square root
	double arg = c2 * c2 - 4.0 * c1 * c3;

	// Ray misses Sphere
	if (arg < 0) return false;

	// One solution, touches the side
	if (arg < COMPARE_ELLIPSE) {
		double t = -c2 / (2.0 * c1);
		x_i = rayStart + rayDirection * (float)t;
	}

	// Time parameter for ray intersection, two possible solutions
	double t1 = (-c2 + glm::sqrt(arg)) / (2 * c1);
	double t2 = (-c2 - glm::sqrt(arg)) / (2 * c1);

	// Take the parameter of the non negative solution, if any
	if (t2 > 0.0f) {
		x_i = rayStart + rayDirection * (float)t2;
	}
	else if (t1 > 0.0f) {
		x_i = rayStart + rayDirection * (float)t1;
	}
	else {
		return false;
	}

	if (glm::length(x_i - ray.getStartpoint()) < minDistance) {
		ray.setColor(color);
		ray.setEndVertex(x_i + glm::normalize(x_i - centreVertex) * 0.001f);
		ray.setObjectNormal(glm::normalize(x_i - centreVertex));
		ray.setObjectMaterial(getMaterial());
		minDistance = glm::length(x_i - ray.getStartpoint());
		return true;
	}

	return false;

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
glm::vec3 Sphere::getCentre() const {
	return centreVertex;
}