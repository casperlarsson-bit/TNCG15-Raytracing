#pragma once
#include "Rectangle.h"
#include "Triangle.h"

class Scene {
public:
	Scene();

	// Setup everything for the scene (Polygons etc.)
	void createScene();

	// Cast and trace a ray
	void castRay(Ray& ray);

	Rectangle rectangles[8]; // RectangleTable for the room = 2 + 6 (floor/roof and walls)
	Triangle triangles[4]; // TriangleTable for the floor and roof
private:
	glm::vec4 vertexTable[50]; // Vertex table
};