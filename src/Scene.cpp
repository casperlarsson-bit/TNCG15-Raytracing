#include "../include/Scene.h"
#include "../include/glm/glm.hpp"
#include <iostream>

const int RANDOM_REFLECTION = 99; // Percentage to continue cast rays in mirror
const double MIRROR_VALUE = 0.95; // How much darker the light should be when returned from a mirror

Scene::Scene() {

}

// Setup everything for the scene (Polygons etc.)
void Scene::createScene() {
	// Set up vertex table

	// Floor
	vertexTable[0] = glm::vec4(0, -6, -5, 1);
	vertexTable[1] = glm::vec4(10, -6, -5, 1);
	vertexTable[2] = glm::vec4(13, 0, -5, 1);
	vertexTable[3] = glm::vec4(10, 6, -5, 1);
	vertexTable[4] = glm::vec4(0, 6, -5, 1);
	vertexTable[5] = glm::vec4(-3, 0, -5, 1);

	// Roof
	vertexTable[6] = glm::vec4(0, -6, 5, 1);
	vertexTable[7] = glm::vec4(10, -6, 5, 1);
	vertexTable[8] = glm::vec4(13, 0, 5, 1);
	vertexTable[9] = glm::vec4(10, 6, 5, 1);
	vertexTable[10] = glm::vec4(0, 6, 5, 1);
	vertexTable[11] = glm::vec4(-3, 0, 5, 1);

	// Floor rectangle vertices
	rectangles[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[3], vertexTable[4]);

	// Floor triangles vertices
	triangles[0].setVertices(vertexTable[1], vertexTable[2], vertexTable[3]);
	triangles[1].setVertices(vertexTable[0], vertexTable[4], vertexTable[5]);


	// Roof rectangle vertices
	rectangles[1].setVertices(vertexTable[6], vertexTable[10], vertexTable[9], vertexTable[7]);

	// Roof triangles vertices
	triangles[2].setVertices(vertexTable[7], vertexTable[9], vertexTable[8]);
	triangles[3].setVertices(vertexTable[6], vertexTable[11], vertexTable[10]);


	// Wall rectangles vertices
	rectangles[2].setVertices(vertexTable[0], vertexTable[6], vertexTable[7], vertexTable[1]);
	rectangles[3].setVertices(vertexTable[1], vertexTable[7], vertexTable[8], vertexTable[2]);
	rectangles[4].setVertices(vertexTable[2], vertexTable[8], vertexTable[9], vertexTable[3]);
	rectangles[5].setVertices(vertexTable[3], vertexTable[9], vertexTable[10], vertexTable[4]);
	rectangles[6].setVertices(vertexTable[4], vertexTable[10], vertexTable[11], vertexTable[5]);
	rectangles[7].setVertices(vertexTable[5], vertexTable[11], vertexTable[6], vertexTable[0]);

	// Calculate all normals
	for (auto& rec : rectangles) {
		rec.calculateNormal();
	}

	for (auto& tri : triangles) {
		tri.calculateNormal();
	}

	// Set colours for Polygons
	rectangles[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	rectangles[1].setColor(ColorDBL(0.1, 0.1, 0.1));
	rectangles[2].setColor(ColorDBL(0.2, 0.66, 0.32));
	rectangles[3].setColor(ColorDBL(0.66, 0.62, 0.2));
	//rectangles[3].setMaterial(Material::MIRROR);
	rectangles[4].setColor(ColorDBL(0.2, 0.27, 0.66));
	rectangles[5].setColor(ColorDBL(0.66, 0.2, 0.2));
	rectangles[6].setColor(ColorDBL(0.2, 0.63, 0.66));
	//rectangles[6].setMaterial(Material::MIRROR);
	rectangles[7].setColor(ColorDBL(0.43, 0.2, 0.66));

	triangles[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangles[1].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangles[2].setColor(ColorDBL(0.1, 0.1, 0.1));
	triangles[3].setColor(ColorDBL(0.1, 0.1, 0.1));

	// Spheres in the scene
	sphereTable[0] = Sphere(1.0, glm::vec4(5, 1, 0, 1), ColorDBL(), Material::MIRROR);

	// Tetrahedron in the scene
	tetrahedronTable[0] = Tetrahedron(glm::vec4(2, 0, -4, 1), glm::vec4(10, 0, -4, 1), glm::vec4(10, -4, -4, 1), glm::vec4(7, -3, 4, 1), ColorDBL(1, 0, 0), Material::LAMBERTIAN);
}

// Cast and trace a ray
void Scene::castRay(Ray& ray, int numReflections) {
	// Go through all rectangles
	for (auto& rect : rectangles) {
		ray.setEndVertex(rect.rayIntersection(ray));
		// Test if inside rectangle, if not go to next rectangle
		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Do different things depending on material of rectangle
		if (rect.getMaterial() == Material::MIRROR) {
			// Reflected direction
			glm::vec3 newDirection = ray.getDirection() - (float)2 * glm::dot(ray.getDirection(), rect.getNormal()) * rect.getNormal();

			Ray newRay{ ray.getEndpoint(), newDirection };

			// Set up doubly linked list
			ray.nextRay = &newRay;
			newRay.prevRay = &ray;

			// Recursively cast ray into scene again until a non mirror is hit
			// Continue to cast ray with 99 % probability, to avoid stack overflow
			// After numReflections (default=3) do probability, otherwise reflect all rays
			if (numReflections > 0) {
				this->castRay(newRay, numReflections-1);
			} 
			else {
				int randomReflection = rand() % 100;
				if (randomReflection < RANDOM_REFLECTION) {
					this->castRay(newRay);
				}
			}

			newRay.prevRay->setColor(newRay.getColor() * MIRROR_VALUE);
		}
	}

	// Go through all triangles
	for (auto& tri : triangles) {
		ray.setEndVertex(tri.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}
	}

	// Go through all spheres
	for (auto& circle : sphereTable) {
		ray.setEndVertex(circle.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Do different things depending on material of rectangle
		if (circle.getMaterial() == Material::MIRROR) {
			glm::vec3 normal = glm::vec3(ray.getEndpoint() - circle.getCentre()); // "Normal" for the circle
			// Reflected direction
			glm::vec3 newDirection = ray.getDirection() - (float)2 * glm::dot(ray.getDirection(), normal) * normal;

			Ray newRay{ ray.getEndpoint(), newDirection };

			// Set up doubly linked list
			ray.nextRay = &newRay;
			newRay.prevRay = &ray;

			// Recursively cast ray into scene again until a non mirror is hit
			// Continue to cast ray with 99 % probability, to avoid stack overflow
			// After numReflections (default=3) do probability, otherwise reflect all rays
			if (numReflections > 0) {
				this->castRay(newRay, numReflections - 1);
			}
			else {
				int randomReflection = rand() % 100;
				if (randomReflection < RANDOM_REFLECTION) {
					this->castRay(newRay);
				}
			}

			newRay.prevRay->setColor(newRay.getColor() * MIRROR_VALUE);
		}
	}

	// Go trhrough all tetrahedrons
	for (auto& tetra : tetrahedronTable) {
		ray.setEndVertex(tetra.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

	}
}