#include "../include/Rectangle.h"
#include <iostream>

// Default constructor
Rectangle::Rectangle() {
	v0 = glm::vec3(0.0f, 0.0f, 0.0f);
	v1 = glm::vec3(1.0f, 0.0f, 0.0f);
	v2 = glm::vec3(1.0f, 1.0f, 0.0f);
	v3 = glm::vec3(0.0f, 1.0f, 0.0f);

	calculateNormal();
}

// Calculate the normal automatically from the vertices
void Rectangle::calculateNormal() {
	glm::vec3 edge1 = glm::vec3(v2 - v1);
	glm::vec3 edge2 = glm::vec3(v0 - v1);

	glm::vec3 newNormal = glm::normalize(glm::cross(edge1, edge2));
	normal = newNormal;
}

// Set the vertices of the Rectangle
void Rectangle::setVertices(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	
	calculateNormal();
}

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
bool Rectangle::rayIntersection(Ray& ray, float& minDistance) const {
	glm::vec3 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	// Normal of Rectangle, and use vertex v0
	glm::vec3 rectangleNormal = glm::normalize(this->getNormal());
	glm::vec3 edge1 = v1 - v0; // Edge connected by v0 and v1
	glm::vec3 edge2 = v3 - v0; // Edge connected by v0 and v3, these two chare same vertex v0

	float t = glm::dot(v0 - rayStart, rectangleNormal) / glm::dot(rayDirection, rectangleNormal);
	glm::vec3 x_i = rayStart + rayDirection * t;

	// If rectangle is hit from back side
	if (glm::dot(glm::cross(rayDirection, edge2), edge1) < COMPARE_ELLIPSE) {
		return false;
	}

	float a = glm::dot(x_i - v0, edge1) / glm::dot(edge1, edge1);
	float b = glm::dot(x_i - v0, edge2) / glm::dot(edge2, edge2);

	// Check if inside Rectangle, 0 <= a <= 1, 0 <= b <= 1
	if ((a >= 0 && a <= 1 && b >= 0 && b <= 1) && glm::length(x_i - ray.getStartpoint()) < minDistance) {
		ray.setColor(color);
		ray.setEndVertex(x_i);
		ray.setObjectNormal(normal);
		ray.setObjectMaterial(getMaterial());
		minDistance = glm::length(x_i - ray.getStartpoint());
		return true;
	}

	// If surface is not hit, return false
	return false;
}