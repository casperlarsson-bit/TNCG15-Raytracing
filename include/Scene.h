#pragma once
#include "Rectangle.h"
#include "Triangle.h"

class Scene {
public:
	Scene();

	// Setup everything for the scene (Polygons etc.)
	void createScene();

	// Cast and trace a ray
	void castRay(Ray& ray, int numReflections = 3);

	// Get the direct light from light source to a specific point
	ColorDBL directLight(glm::vec4 rayPosition, glm::vec3 surfaceNormal);

	// Get the indirect light from other surfaces
	ColorDBL indirectLight(Ray ray, glm::vec3 surfaceNormal);

	// Create a local coordinate system with orthogonal axes
	void createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const;

private:
	glm::vec4 vertexTable[50]; // Vertex table
	Rectangle rectangleTable[8]; // RectangleTable for the room = 2 + 6 (floor/roof and walls)
	Triangle triangleTable[4]; // TriangleTable for the floor and roof
};