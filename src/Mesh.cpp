#include "../include/Mesh.h"
#include <iostream>

// Default constructor
Mesh::Mesh(const std::string& _filename, const glm::vec3& _position, const ColorDBL& _color, const Material& _material) {
	color = _color;
	material = _material;

	loadOBJ(_filename);

	// Translate vertices by position
	for (auto vertex : vertices) {
		vertex += _position;
	}
}

// Get the colour of the mesh
ColorDBL Mesh::getColor() const {
	return color;
}

// Get what material the the mesh is made of
Material Mesh::getMaterial() const {
	return material;
}

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
bool Mesh::rayIntersection(Ray& ray, float& minDistance) const {
	bool hit = false;

	for (size_t i = 0; i < vertices.size(); i += 3) {
		Triangle meshTriangle;
		meshTriangle.setVertices(vertices[i], vertices[i + 1], vertices[i + 2]);
		meshTriangle.setColor(color);
		meshTriangle.setMaterial(material);
		meshTriangle.calculateNormal();


		return false;
		// Will never work
		meshTriangle.rayIntersection(ray, minDistance);

		
	}

	return hit;
}

// Load the obj file from string path
void Mesh::loadOBJ(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open OBJ file: " + filename);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v") {
			glm::vec3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (type == "vn") {
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}

		// Måste skapa trianglarna här, eftersom obj filen säger vilka vertexar som skapar dem
	}

	file.close();
}