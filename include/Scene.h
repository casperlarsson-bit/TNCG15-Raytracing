/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include "Rectangle.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Tetrahedron.h"
#include "Cube.h"

class Scene {
public:
	// Default constructor to setup everything for the scene (Vertextable, Polygons etc.)
	Scene();

	// Cast and trace a ray
	void castRay(Ray& ray, int numReflections = 3);
private:
	// Handle different kind of reflections (Lambertian, Mirror, Transparent) on dirrefent Polygons
	void handleReflection(Ray& ray, int numReflections);

	// Get the direct light from light source to a specific point
	ColorDBL directLight(const Ray& ray);

	// Get the indirect light from other surfaces
	ColorDBL indirectLight(const Ray& ray);

	// Create a local coordinate system with orthogonal axes
	void createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const;

	// Calculate the reflected ray, cast it and set its colour
	void reflectRay(Ray& ray);

	// Calculate the refracted ray, cast it and set its colour
	void refractRay(Ray& ray, float R);

	glm::vec3 vertexTable[16]; // Vertex table
	Rectangle rectangleTable[9]; // Rectangle Table for the room = 2 + 6 (floor/roof and walls)
	Triangle triangleTable[4]; // Triangle Table for the floor and roof
	Sphere sphereTable[5]; // Sphere Table with all object spheres in the scene
	Tetrahedron tetrahedronTable[1]; // Tetrahedron Table
	Cube cubeTable[1]; // Cube table
};