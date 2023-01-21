/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#include "../include/Triangle.h"
#include <iostream>

// Default constructor
Triangle::Triangle() {
	v0 = glm::vec3(1.0f, 0.0f, 0.0f);
	v1 = glm::vec3(0.0f, 1.0f, 0.0f);
	v2 = glm::vec3(0.0f, 0.0f, 1.0f);

	calculateNormal();
}

// Calculate the normal automatically from the vertices
void Triangle::calculateNormal() {
	glm::vec3 edge1 = v2 - v1;
	glm::vec3 edge2 = v0 - v1;

	glm::vec3 newNormal = glm::normalize(glm::cross(edge1, edge2));
	normal = newNormal;
}

// Set the vertices of the Triangle
void Triangle::setVertices(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;

	calculateNormal();
}

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
bool Triangle::rayIntersection(Ray& ray, float& minDistance) const {
	glm::vec3 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 rayToVertex = glm::vec3(rayStart - v0);
	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;

	// Get parameters P=DxE2 and Q=TxE1
	glm::vec3 P = glm::cross(rayDirection, edge2);
	glm::vec3 Q = glm::cross(rayToVertex, edge1);
	float PdotEdge = glm::dot(P, edge1);

	// If triangle is hit from back side
	if (PdotEdge < COMPARE_ELLIPSE) return false;
	if (fabs(PdotEdge) < COMPARE_ELLIPSE) return false;

	// Parameters (u,v) to test if Ray is inside Triangle
	float u = glm::dot(P, rayToVertex) / PdotEdge;
	float v = glm::dot(Q, rayDirection) / PdotEdge;

	float t = glm::dot(Q, edge2) / PdotEdge;
	glm::vec3 x_i = rayStart + rayDirection * t;

	// Check if outside Triangle, u >= 0, v >= 0, u+v <= 1. If x_i length is too big return false
	if ((u >= 0 && v >= 0 && u + v <= 1) && glm::length(x_i) < minDistance) {
		// Carry on if inside Triangle, to calculate set parameters
		
		// Set the ray colour either to the colour of the rectangle or load from texture
		if (filename == "") {
			ray.setColor(color);
		}
		else {
			glm::vec3 intersectionVector = x_i - v2; // Get the vector from the corner towards the intersected point
			glm::vec3 bottomEdge = v0 - v2; // Bottom of the triangle
			glm::vec3 leftEdge = v1 - 0.5f * bottomEdge; // Height of triangle
			float aScalar = glm::dot(intersectionVector, glm::normalize(bottomEdge)); // Get the scaling factor of the projected vector
			glm::vec3 a1 = aScalar * glm::normalize(bottomEdge); // Project intersectionVector into bottomEdge
			glm::vec3 a2 = intersectionVector - a1; // The projected vector on height

			// Get the texture coordinates (x,y) to read from the file
			int x = std::min((int)((glm::length(a1) / glm::length(bottomEdge)) * textureWidth), textureWidth - 1);
			int y = std::min((int)((1 - glm::length(a2) / glm::length(leftEdge)) * textureHeight), textureHeight - 1);

			const size_t RGBA = 4;
			size_t index = RGBA * (y * textureWidth + x);

			int R = static_cast<int>(texture[index + 0]);
			int G = static_cast<int>(texture[index + 1]);
			int B = static_cast<int>(texture[index + 2]);

			ray.setColor(ColorDBL(R, G, B));
		}

		ray.setEndVertex(x_i + normal * 0.001f);
		ray.setObjectNormal(normal);
		ray.setObjectMaterial(getMaterial());
		minDistance = glm::length(x_i);
		return true;
	}

	// Hit but not within the range or an object is in front already
	return false;
}