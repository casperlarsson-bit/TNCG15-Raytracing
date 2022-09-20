#pragma once
#include "Rectangle.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Tetrahedron.h"

class Scene {
public:
	Scene();

	// Setup everything for the scene (Polygons etc.)
	void createScene();

	// Cast and trace a ray
	void castRay(Ray& ray, int numReflections = 3);

	Rectangle rectangles[8]; // RectangleTable for the room = 2 + 6 (floor/roof and walls)
	Triangle triangles[4]; // TriangleTable for the floor and roof
	Sphere sphereTable[1]; // SphereTable with all object spheres in the scene
	Tetrahedron tetrahedronTable[1];
private:
	glm::vec4 vertexTable[50]; // Vertex table
};