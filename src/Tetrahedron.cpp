#include "../include/Tetrahedron.h"
#include <iostream>

// Default constructor
Tetrahedron::Tetrahedron() {
	glm::vec3 _midVertex = glm::vec3(5, 0, 1);

	vertexTable[0] = glm::vec4(_midVertex.x, _midVertex.y, 1 + _midVertex.z, 1);
	vertexTable[1] = glm::vec4(-1 + _midVertex.x, _midVertex.y, -1 + _midVertex.z, 1);
	vertexTable[2] = glm::vec4(_midVertex.x, -1 + _midVertex.y, -1 + _midVertex.z, 1);
	vertexTable[3] = glm::vec4(_midVertex.x, 1 + _midVertex.y, -1 + _midVertex.z, 1);

	triangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2]);
	triangleTable[1].setVertices(vertexTable[3], vertexTable[1], vertexTable[0]);
	triangleTable[2].setVertices(vertexTable[3], vertexTable[2], vertexTable[1]);
	triangleTable[3].setVertices(vertexTable[3], vertexTable[0], vertexTable[2]);

	material = Material::LAMBERTIAN;
	for (auto& triangle : triangleTable) {
		triangle.setColor(ColorDBL());
		triangle.calculateNormal();
	}
}

// Value constructor
Tetrahedron::Tetrahedron(glm::vec3 _midVertex, ColorDBL _color, Material _material) {
	vertexTable[0] = glm::vec4(_midVertex.x, _midVertex.y, 1 + _midVertex.z, 1);
	vertexTable[1] = glm::vec4(-1 + _midVertex.x, _midVertex.y, -1 + _midVertex.z, 1);
	vertexTable[2] = glm::vec4(_midVertex.x, -1 + _midVertex.y, -1 + _midVertex.z, 1);
	vertexTable[3] = glm::vec4(_midVertex.x, 1 + _midVertex.y, -1 + _midVertex.z, 1);

	triangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2]);
	triangleTable[1].setVertices(vertexTable[3], vertexTable[1], vertexTable[0]);
	triangleTable[2].setVertices(vertexTable[3], vertexTable[2], vertexTable[1]); // Bottom
	triangleTable[3].setVertices(vertexTable[3], vertexTable[0], vertexTable[2]);

	material = _material;
	color = _color;

	for (auto& triangle : triangleTable) {
		triangle.setColor(_color);
		triangle.setMaterial(_material);
		triangle.calculateNormal();
	}
}

// Calculate the intersection of a ray and the surface
// D*N < 0 for correct intersection
void Tetrahedron::rayIntersection(Ray& ray, double& minDistance) const {
	for (auto& triangle : triangleTable) {
		if (glm::dot(triangle.getNormal(), ray.getDirection()) > COMPARE_ELLIPSE) continue;
		if (triangle.rayIntersection(ray, minDistance)) break;
	}

	//triangleTable[0].rayIntersection(ray, minDistance);
	//triangleTable[1].rayIntersection(ray, minDistance);
	//if (triangleTable[3].rayIntersection(ray, minDistance)) std::cout << "Went wrong";
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
	for (auto& triangle : triangleTable) {
		triangle.setColor(_color);
	}
}