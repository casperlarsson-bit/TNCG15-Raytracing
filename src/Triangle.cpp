#include "../include/Triangle.h"

// Default constructor
Triangle::Triangle() {

}

// Set the vertices of the Triangle
void Triangle::setVertices(glm::vec4 _v0, glm::vec4 _v1, glm::vec4 _v2) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
}

// Calculate the intersection of a ray and the surface
// Return the vertex where it hits
glm::vec4 Triangle::rayIntersection(Ray& ray) {

}