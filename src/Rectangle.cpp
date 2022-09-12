#include "../include/Rectangle.h"
#include <iostream>

// Default constructor
Rectangle::Rectangle() {

}

// Calculate the normal automatically from the vertices
void Rectangle::calculateNormal() {
	glm::vec3 edge1 = glm::vec3(v2 - v1);
	glm::vec3 edge2 = glm::vec3(v0 - v1);

	glm::vec3 newNormal = glm::normalize(glm::cross(edge1, edge2));
	normal = newNormal;
}

// Set the vertices of the Rectangle
void Rectangle::setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2, glm::vec4 _v3) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
}

// Calculate the intersection of a ray and the surface
// Return the vertex where it hits
glm::vec4 Rectangle::rayIntersection(Ray& ray) const {
	glm::vec4 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	// Normal of Rectangle, and use vertex v0
	glm::vec3 rectangleNormal = glm::normalize(this->getNormal());
	glm::vec4 edge1 = v1 - v0; // Edge connected by v0 and v1
	glm::vec4 edge2 = v3 - v0; // Edge connected by v0 and v3, these two chare same vertex v0

	double t = glm::dot(glm::vec3(v0 - rayStart), rectangleNormal) / glm::dot(rayDirection, rectangleNormal);
	glm::vec4 x_i = rayStart + glm::vec4(rayDirection, 1) * (float)t;

	double a = glm::dot(x_i - v0, edge1) / glm::dot(edge1, edge1);
	double b = glm::dot(x_i - v0, edge2) / glm::dot(edge2, edge2);

	// Check if inside Rectangle, 0 <= a <= 1, 0 <= b <= 1. Should not compare double directly
	if (a >= 0 && a <= 1 && b >= 0 && b <= 1) {
		ray.setColor(color);
		return x_i;
	}

	// If surface is not hit, return null, is ther a better way?
	return glm::vec4(NULL, NULL, NULL, NULL);
}