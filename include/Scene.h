#pragma once
#include "Rectangle.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Tetrahedron.h"

class Scene {
public:
	// Default constructor to setup everything for the scene (Vertextable, Polygons etc.)
	Scene();

	// Cast and trace a ray
	void castRay(Ray& ray, int numReflections = 3);
private:
	// Handle different kind of reflections (Lambertian, Mirror, Transparent) on dirrefent Polygons
	void handleReflection(Ray& ray, Polygon& polygon, int numReflections);

	// Overloaded handleReflection to do the same thing but for Spheres, since the normal is computed in a different way
	void handleReflection(Ray& ray, int numReflections);

	// Get the direct light from light source to a specific point
	ColorDBL directLight(const Ray& ray);

	// Get the indirect light from other surfaces
	ColorDBL indirectLight(const Ray& ray);

	// Create a local coordinate system with orthogonal axes
	void createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const;

	glm::vec4 vertexTable[12]; // Vertex table
	Rectangle rectangleTable[8]; // Rectangle Table for the room = 2 + 6 (floor/roof and walls)
	Triangle triangleTable[4]; // Triangle Table for the floor and roof
	Sphere sphereTable[5]; // Sphere Table with all object spheres in the scene
	Tetrahedron tetrahedronTable[1]; // Tetrahedron Table
};