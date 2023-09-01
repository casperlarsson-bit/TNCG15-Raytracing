#include "../include/Mesh.h"
#include <iostream>

// Default constructor
Mesh::Mesh(const std::string& _filename, const glm::vec3& _position, const ColorDBL& _color, const Material& _material) {
	color = _color;
	material = _material;

	loadOBJ(_filename, _position);

	// Translate vertices by position
	for (auto vertex : vertices) {
		//vertex += _position;
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

	/*for (size_t i = 0; i < vertices.size(); i += 3) {
		Triangle meshTriangle;
		meshTriangle.setVertices(vertices[i], vertices[i + 1], vertices[i + 2]);
		meshTriangle.setColor(color);
		meshTriangle.setMaterial(material);
		meshTriangle.calculateNormal();


		meshTriangle.rayIntersection(ray, minDistance);
	}*/

	for (auto triangle : triangles) {
		//std::cout << triangle.getColor().blue << "\n";
		if (triangle.rayIntersection(ray, minDistance)) hit = true;

	}

	return hit;
}

// Load the obj file from string path
void Mesh::loadOBJ(const std::string& filename, const glm::vec3& position) {
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
			vertices.push_back(vertex + position);
		}
		else if (type == "vn") {
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		// Works for GPT obj file, no texture index
		/*
		else if (type == "f") {
			std::vector<int> indices;
			int vertexIndex, normalIndex;
			char slash;
			while (iss >> vertexIndex >> slash) {
				//std::cout << vertexIndex << " ";
				indices.push_back(vertexIndex - 1); // OBJ indices are 1-based
				if (iss.peek() == '/') {
					iss >> slash;
					if (iss.peek() != '/') {
						iss >> normalIndex;
						//indices.push_back(normalIndex - 1); // OBJ indices are 1-based
					}
				}
			}
			//std::cout << std::endl;
			vertexIndices.push_back(indices);
		}
		*/
		else if (type == "f") {
			std::vector<int> indices;
			int vertexIndex, textureIndex, normalIndex;
			char slash;

			while (iss >> vertexIndex >> slash >> textureIndex >> slash >> normalIndex) {
				indices.push_back(vertexIndex - 1); // OBJ indices are 1-based
			}

			vertexIndices.push_back(indices);
		}
	}

	// Create triangles from vertex indices
	for (const auto& indices : vertexIndices) {
		// Is a triangle
		if (indices.size() == 3) {
			Triangle meshTriangle;
			meshTriangle.setVertices(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);
			meshTriangle.setColor(color);
			meshTriangle.setMaterial(material);
			meshTriangle.calculateNormal();

			triangles.push_back(meshTriangle);
		}
		// Add possibility to render rectangles from obj file
		else if (indices.size() == 4) throw std::runtime_error("Rectangles not implemented for obj");
	}

	file.close();
}