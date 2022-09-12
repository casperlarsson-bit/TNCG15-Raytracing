#include "../include/Triangle.h"
#include <iostream>

// Default constructor
Triangle::Triangle() {

}

// Calculate the normal automatically from the vertices
void Triangle::calculateNormal() {
	glm::vec3 edge1 = glm::vec3(v2 - v1);
	glm::vec3 edge2 = glm::vec3(v0 - v1);

	glm::vec3 newNormal = glm::normalize(glm::cross(edge1, edge2));
	normal = newNormal;
}

// Set the vertices of the Triangle
void Triangle::setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
}

// Calculate the intersection of a ray and the surface
// Return the vertex where it hits
glm::vec4 Triangle::rayIntersection(Ray& ray) const {
	glm::vec4 rayStart = ray.getStartpoint();
	glm::vec4 rayEnd = ray.getEndpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 rayToVertex = glm::vec3(rayStart - v0);
	glm::vec3 edge1 = glm::vec3(v1 - v0);
	glm::vec3 edge2 = glm::vec3(v2 - v0);

	// Get parameters P=DxE2 and Q=TxE1
	glm::vec3 P = glm::cross(rayDirection, edge2);
	glm::vec3 Q = glm::cross(rayToVertex, edge1);

	// Parameters (u,v) to test if Ray is inside Triangle
	double u = glm::dot(P, rayToVertex) / glm::dot(P, edge1);
	double v = glm::dot(Q, rayDirection) / glm::dot(P, edge1);

	// Check if outside Triangle, u >= 0, v >= 0, u+v <= 1. Should not compare double directly
	if (!(u >= 0 && v >= 0 && u + v <= 1)) {
		// If surface is not hit, return null, is ther a better way?
		return glm::vec4(NULL, NULL, NULL, NULL);
	}
	// Carry on if inside Triangle, to calculate t and x_i
	double t = glm::dot(Q, edge2) / glm::dot(P, edge1);
	ray.setColor(color);
	return rayStart + glm::vec4(rayDirection, 1) * (float)t;
}