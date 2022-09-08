#include "../include/Rectangle.h"

// Default constructor
Rectangle::Rectangle() {

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
glm::vec4 Rectangle::rayIntersection(Ray& ray) {

}