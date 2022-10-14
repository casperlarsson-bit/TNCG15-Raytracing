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
glm::vec4 Triangle::rayIntersection(Ray& ray, double& minDistance) const {
	glm::vec4 rayStart = ray.getStartpoint();
	glm::vec4 rayEnd = ray.getEndpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 rayToVertex = glm::vec3(rayStart - v0);
	glm::vec3 edge1 = glm::vec3(v1 - v0);
	glm::vec3 edge2 = glm::vec3(v2 - v0);

	// Get parameters P=DxE2 and Q=TxE1
	glm::vec3 P = glm::cross(rayDirection, edge2);
	glm::vec3 Q = glm::cross(rayToVertex, edge1);

	// If triangle is hit from back side
	if (glm::dot(P, edge1) < COMPARE_ELLIPSE) {
		return glm::vec4(NULL, NULL, NULL, NULL);
	}

	// Parameters (u,v) to test if Ray is inside Triangle
	double u = glm::dot(P, rayToVertex) / glm::dot(P, edge1);
	double v = glm::dot(Q, rayDirection) / glm::dot(P, edge1);

	double t = glm::dot(Q, edge2) / glm::dot(P, edge1);
	glm::vec4 x_i = rayStart + glm::vec4(rayDirection, 1) * (float)t;

	// Check if outside Triangle, u >= 0, v >= 0, u+v <= 1. If t is too big return false. Should not compare double directly @TODO
	if ((u >= 0 && v >= 0 && u + v <= 1) && glm::length(x_i) < minDistance) {
		// Carry on if inside Triangle, to calculate x_i
		ray.setColor(color);
		ray.setEndVertex(x_i);
		minDistance = glm::length(x_i);
		return x_i;
	}
	return glm::vec4(NULL, NULL, NULL, NULL);
	
}