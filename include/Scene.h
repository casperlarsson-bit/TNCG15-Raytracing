#pragma once
#include "Rectangle.h"
#include "Triangle.h"

class Scene {
public:
	Scene();

	// Setup everything for the scene (Polygons etc.)
	void createScene();
private:
	Rectangle rectangles[8]; // Rectangles for the room = 2 + 6 (floor/roof and walls)
	Triangle triangles[4]; // Triangles for the floor and roof
};