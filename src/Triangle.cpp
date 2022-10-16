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
	/*glm::vec3 rayStart = ray.getStartpoint();
	glm::vec3 rayEnd = ray.getEndpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 rayToVertex = glm::vec3(rayStart - v0);
	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;

	// Get parameters P=DxE2 and Q=TxE1
	glm::vec3 P = glm::cross(rayDirection, edge2);
	glm::vec3 Q = glm::cross(rayToVertex, edge1);

	// If triangle is hit from back side
	if (glm::dot(P, edge1) < COMPARE_ELLIPSE) {
		return false;
	}

	if (fabs(glm::dot(P, edge1)) < COMPARE_ELLIPSE) {
		return false;
	}

	// Parameters (u,v) to test if Ray is inside Triangle
	float u = glm::dot(P, rayToVertex) / glm::dot(P, edge1);
	float v = glm::dot(Q, rayDirection) / glm::dot(P, edge1);

	float t = glm::dot(Q, edge2) / glm::dot(P, edge1);
	glm::vec3 x_i = rayStart + rayDirection * t;

	// Check if outside Triangle, u >= 0, v >= 0, u+v <= 1. If t is too big return false. Should not compare float directly @TODO
	if ((u >= 0 && v >= 0 && u + v <= 1) && glm::length(x_i - ray.getStartpoint()) < minDistance) {
		// Carry on if inside Triangle, to calculate x_i
		ray.setColor(color);
		ray.setEndVertex(x_i + normal * 0.001f);
		ray.setObjectNormal(normal);
		ray.setObjectMaterial(getMaterial());
		minDistance = glm::length(x_i - ray.getStartpoint());
		return true;
	}

	// Hit but not within the range or an object is in front already
	return false;*/

	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;
	glm::vec3 pvec = glm::cross(ray.getDirection(), edge2);
	glm::vec3 qvec = glm::cross(ray.getStartpoint() - v0, edge1);
	glm::vec3 tvec = ray.getStartpoint() - v0;

	const float kEpsilon = 0.00001f;

	float det = glm::dot(edge1, pvec);

	// if the determinant is negative the triangle is back-facing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;

	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < kEpsilon) return false;

	float invDet = 1.0f / det;

	float u = glm::dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1) return false;

	float v = glm::dot(ray.getDirection(), qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	float t = glm::dot(edge2, qvec) * invDet;

	if (glm::length(glm::vec3(ray.getStartpoint() + ray.getDirection() * t)) < minDistance) {
		ray.setObjectNormal(this->getNormal());
		ray.setEndVertex(ray.getStartpoint() + ray.getDirection() * t + this->getNormal() * 0.001f); 
		ray.setColor(getColor());
		minDistance = glm::length(ray.getDirection() * t);
		ray.setObjectMaterial(getMaterial());
	}

	return true;
}