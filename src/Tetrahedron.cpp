#include "../include/Tetrahedron.h"
#include <iostream>

// Default constructor
Tetrahedron::Tetrahedron() {
	vertexTable[0] = glm::vec4(4, 0, -4, 1);
	vertexTable[1] = glm::vec4(5, 1, -4, 1);
	vertexTable[2] = glm::vec4(5, -1, -4, 1);
	vertexTable[3] = glm::vec4(4.5, 0,-2, 1);

	triangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2]);
	triangleTable[1].setVertices(vertexTable[3], vertexTable[1], vertexTable[0]);
	triangleTable[2].setVertices(vertexTable[3], vertexTable[2], vertexTable[1]);
	triangleTable[3].setVertices(vertexTable[3], vertexTable[0], vertexTable[2]);

	material = Material::LAMBERTIAN;
	for (auto& triangle : triangleTable) {
		triangle.setColor(ColorDBL());
	}
}

// Value constructor
Tetrahedron::Tetrahedron(glm::vec4 v0, glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, ColorDBL _color, Material _material) {
	vertexTable[0] = v0;
	vertexTable[1] = v1;
	vertexTable[2] = v2;
	vertexTable[3] = v3;

	triangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2]);
	triangleTable[1].setVertices(vertexTable[3], vertexTable[1], vertexTable[0]);
	triangleTable[2].setVertices(vertexTable[3], vertexTable[2], vertexTable[1]);
	triangleTable[3].setVertices(vertexTable[3], vertexTable[0], vertexTable[2]);

	material = _material;
	double n = 1.0;
	for (auto& triangle : triangleTable) {
		triangle.setColor(_color * n);
		n /= 1.5;
	}
}

// Calculate the intersection of a ray and the surface
// Return the vertex where it hits
// D*N < 0 for correct intersection
glm::vec4 Tetrahedron::rayIntersection(Ray& ray) const {


	for (auto& triangle : triangleTable) {
		if (glm::dot(triangle.getNormal(), ray.getDirection()) > 0.01) continue;
		return triangle.rayIntersection(ray);
	}

}

// Get what material the Tetrahedron is made of
Material Tetrahedron::getMaterial() const {
	return material;
}

// Sets the material of the Tetrahedron
void Tetrahedron::setMaterial(Material _material) {
	material = _material;
}

// Get the colour of the Tetrahedron
ColorDBL Tetrahedron::getColor() const {
	return color;
}

// Set the colour of the Tetrahedron
void Tetrahedron::setColor(ColorDBL _color) {
	color = _color;
}