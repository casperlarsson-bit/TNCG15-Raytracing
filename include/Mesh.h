#pragma once
#include <fstream>
#include <sstream>
#include "Triangle.h"

class Mesh {
public:
	// Default constructor
	Mesh(const std::string& _filename, const glm::vec3& _position, const ColorDBL& _color, const Material& _material);

	// Get the colour of the mesh
	ColorDBL getColor() const;

	// Get what material the the mesh is made of
	Material getMaterial() const;

	// Calculate the intersection of a ray and the surface
	// Return true if hits the surface
	bool rayIntersection(Ray& ray, float& minDistance) const;

	ColorDBL color;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
private:
	// Load the obj file from string path
	void loadOBJ(const std::string& filename);

	Material material;
	float rho;
};