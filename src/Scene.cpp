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
	rectangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[3], vertexTable[4]);

	// Floor triangles vertices
	triangleTable[0].setVertices(vertexTable[1], vertexTable[2], vertexTable[3]);
	triangleTable[1].setVertices(vertexTable[0], vertexTable[4], vertexTable[5]);


	// Roof rectangle vertices
	rectangleTable[1].setVertices(vertexTable[6], vertexTable[10], vertexTable[9], vertexTable[7]);

	// Roof triangles vertices
	triangleTable[2].setVertices(vertexTable[7], vertexTable[9], vertexTable[8]);
	triangleTable[3].setVertices(vertexTable[6], vertexTable[11], vertexTable[10]);


	// Wall rectangles vertices
	rectangleTable[2].setVertices(vertexTable[0], vertexTable[6], vertexTable[7], vertexTable[1]);
	rectangleTable[3].setVertices(vertexTable[1], vertexTable[7], vertexTable[8], vertexTable[2]);
	rectangleTable[4].setVertices(vertexTable[2], vertexTable[8], vertexTable[9], vertexTable[3]);
	rectangleTable[5].setVertices(vertexTable[3], vertexTable[9], vertexTable[10], vertexTable[4]);
	rectangleTable[6].setVertices(vertexTable[4], vertexTable[10], vertexTable[11], vertexTable[5]);
	rectangleTable[7].setVertices(vertexTable[5], vertexTable[11], vertexTable[6], vertexTable[0]);

	// Calculate all normals
	for (auto& rec : rectangleTable) {
		rec.calculateNormal();
		rec.setColor(ColorDBL(1.0, 1.0, 1.0));
	}

	for (auto& tri : triangleTable) {
		tri.calculateNormal();
		tri.setColor(ColorDBL(1.0, 1.0, 1.0));
	}

	// Set colours for Polygons
	/*rectangles[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	rectangles[1].setColor(ColorDBL(0.1, 0.1, 0.1));
	rectangles[2].setColor(ColorDBL(0.2, 0.66, 0.32));
	// rectangles[3].setColor(ColorDBL(0.2, 0.63, 0.66));
	rectangles[3].setMaterial(Material::MIRROR);
	rectangles[4].setColor(ColorDBL(0.2, 0.27, 0.66));
	rectangles[5].setColor(ColorDBL(0.66, 0.2, 0.2));
	rectangles[6].setColor(ColorDBL(0.66, 0.62, 0.2));
	rectangles[6].setMaterial(Material::MIRROR);
	rectangles[7].setColor(ColorDBL(0.43, 0.2, 0.66));

	triangles[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangles[1].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangles[2].setColor(ColorDBL(0.1, 0.1, 0.1));
	triangles[3].setColor(ColorDBL(0.1, 0.1, 0.1));*/
}

// Cast and trace a ray
void Scene::castRay(Ray& ray, int numReflections) {
	for (auto& rect : rectangleTable) {
		ray.setEndVertex(rect.rayIntersection(ray));
		// Test if inside rectangle, if not go to next rectangle
		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Do different things depending on material of rectangle
		// Mirror, reflect ray and cast it again
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
		// Lambertian surface, cast ray to the light source to get light on the point
		else if (rect.getMaterial() == Material::LAMBERTIAN) {

		}
	}

	// @TODO Fix above code for triangles as well
	for (auto& tri : triangleTable) {
		ray.setEndVertex(tri.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}
	}

}

// Get the direct light from light source to a specific point
ColorDBL Scene::directLight(glm::vec4 rayPosition) {
	// Define area light
	glm::vec4 v0 = glm::vec4(-2, -2, 5, 1);
	glm::vec4 v1 = glm::vec4(2, -2, 5, 1);
	glm::vec4 v2 = glm::vec4(-2, 2, 5, 1);
	glm::vec4 v3 = glm::vec4(2, 2, 5, 1);

	glm::vec4 e1 = v2 - v1;
	glm::vec4 e2 = v0 - v1;

	glm::vec3 lightNormal = glm::normalize(glm::cross(glm::vec3(e2), glm::vec3(e1)));

	// glm::vec3 rayLightDistanceVector = glm::vec3(rayPosition - xi); // in loop


	return ColorDBL();
}