#pragma once
#include "Rectangle.h"
#include "Triangle.h"

class Scene {
public:
	// Default constructor to setup everything for the scene (Vertextable, Polygons etc.)
	Scene();

	// Cast and trace a ray
	void castRay(Ray& ray, int numReflections = 3);

	// Get the direct light from light source to a specific point
	ColorDBL directLight(const Ray& ray);

	// Get the indirect light from other surfaces
	ColorDBL indirectLight(const Ray& ray);

	// Create a local coordinate system with orthogonal axes
	void createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const;

private:
	glm::vec4 vertexTable[12]; // Vertex table
	Rectangle rectangleTable[8]; // RectangleTable for the room = 2 + 6 (floor/roof and walls)
	Triangle triangleTable[4]; // TriangleTable for the floor and roof
};