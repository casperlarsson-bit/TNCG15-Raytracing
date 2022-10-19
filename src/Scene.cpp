#include "../include/Scene.h"
#include "../include/glm/glm.hpp"
#include <iostream>
#include <math.h>
#include <random> // Default random engine

#define M_PI 3.14159265358979323846f  // Pi

// Should replace above function
std::default_random_engine seed;
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);


const int RANDOM_REFLECTION = 99; // Percentage to continue cast rays in mirror, remove this
const float MIRROR_VALUE = 0.95f; // How much darker the light should be when returned from a mirror, for realism
const int NUMBER_OF_SHADOW_RAYS = 3;

// Default constructor to setup everything for the scene (Vertextable, Polygons etc.)
Scene::Scene() {
	// Set up vertex table

	// Floor
	vertexTable[0] = glm::vec3(0.0f, -6.0f, -5.0f);
	vertexTable[1] = glm::vec3(10.0f, -6.0f, -5.0f);
	vertexTable[2] = glm::vec3(13.0f, 0.0f, -5.0f);
	vertexTable[3] = glm::vec3(10.0f, 6.0f, -5.0f);
	vertexTable[4] = glm::vec3(0.0f, 6.0f, -5.0f);
	vertexTable[5] = glm::vec3(-3.0f, 0.0f, -5.0f);

	// Roof
	vertexTable[6] = glm::vec3(0.0f, -6.0f, 5.0f);
	vertexTable[7] = glm::vec3(10.0f, -6.0f, 5.0f);
	vertexTable[8] = glm::vec3(13.0f, 0.0f, 5.0f);
	vertexTable[9] = glm::vec3(10.0f, 6.0f, 5.0f);
	vertexTable[10] = glm::vec3(0.0f, 6.0f, 5.0f);
	vertexTable[11] = glm::vec3(-3.0f, 0.0f, 5.0f);

	// Lamp
	vertexTable[12] = glm::vec3(5.0f, 1.0f, 4.8f);
	vertexTable[13] = glm::vec3(6.0f, 1.0f, 4.8f);
	vertexTable[14] = glm::vec3(6.0f, 0.0f, 4.8f);
	vertexTable[15] = glm::vec3(5.0f, 0.0f, 4.8f);


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

	// Light source
	rectangleTable[8].setVertices(vertexTable[12], vertexTable[13], vertexTable[14], vertexTable[15]);
	rectangleTable[8].setMaterial(Material::LIGHT);


	// Calculate all normals
	for (auto& rectangle : rectangleTable) {
		rectangle.calculateNormal();
		rectangle.setColor(ColorDBL(1.0f, 1.0f, 1.0f));
	}

	for (auto& triangle : triangleTable) {
		triangle.calculateNormal();
		triangle.setColor(ColorDBL(1.0f, 1.0f, 1.0f));
	}

	// Set colours for Polygons
	rectangleTable[0].setColor(ColorDBL(0.8f, 0.8f, 0.8f));
	rectangleTable[1].setColor(ColorDBL(0.1f, 0.1f, 0.1f));
	rectangleTable[2].setColor(ColorDBL(0.2f, 0.66f, 0.32f));
	rectangleTable[3].setColor(ColorDBL(0.66f, 0.62f, 0.2f));
	// rectangleTable[3].setMaterial(Material::MIRROR);
	rectangleTable[4].setColor(ColorDBL(0.2f, 0.27f, 0.66f));
	rectangleTable[5].setColor(ColorDBL(0.66f, 0.2f, 0.2f));
	rectangleTable[6].setColor(ColorDBL(0.2f, 0.63f, 0.66f));
	// rectangleTable[6].setMaterial(Material::MIRROR);
	rectangleTable[7].setColor(ColorDBL(0.43f, 0.2f, 0.66f));

	triangleTable[0].setColor(ColorDBL(0.8f, 0.8f, 0.8f));
	triangleTable[1].setColor(ColorDBL(0.8f, 0.8f, 0.8f));
	triangleTable[2].setColor(ColorDBL(0.1f, 0.1f, 0.1f));
	triangleTable[3].setColor(ColorDBL(0.1f, 0.1f, 0.1f));

	// Spheres in the scene
	// sphereTable[0] = Sphere(1.0f, glm::vec3(6.0f, 1.0f, -1.0f), ColorDBL(1.0f, 0.0f, 1.0f), Material::MIRROR);
	//sphereTable[0] = Sphere(0.8f, glm::vec3(4.0f, -2.0f, -2.0f), ColorDBL(1.0f, 0.0f, 1.0f), Material::TRANSPARENT);

	// Temporarily copy
	sphereTable[0] = Sphere(1.0f, glm::vec3(4.5f, 3.0f, -3.0f), ColorDBL(0.5f, 0.5f, 0.5f), Material::MIRROR); // MIRROR
	sphereTable[1] = Sphere(1.0f, glm::vec3(6.0f, -3.0f, -2.0f), ColorDBL(0.5f, 0.5f, 0.5f), Material::TRANSPARENT); // TRANSPARENT
	sphereTable[2] = Sphere(1.0f, glm::vec3(5.0f, -2.0f, -4.0f), ColorDBL(1.0f, 1.0f, 1.0f), Material::LAMBERTIAN);
	sphereTable[3] = Sphere(1.0f, glm::vec3(10.0f, 0.2f, -1.0f), ColorDBL(0.5f, 0.5f, 0.5f), Material::TRANSPARENT); // TRANSPARENT
	sphereTable[4] = Sphere(0.5f, glm::vec3(6.0f, 3.0f, -1.0f), ColorDBL(0.8f, 0.2f, 0.2f), Material::LAMBERTIAN);

	// Tetrahedron in the scene
	tetrahedronTable[0] = Tetrahedron(glm::vec3(8.0f, 2.0f, -1.0f), ColorDBL(0.96f, 0.04f, 0.32f), Material::LAMBERTIAN);
}

// Cast and trace a ray
void Scene::castRay(Ray& ray, int numReflections) {
	float minDistance = 1000.0f; // Store the distance to the closest object a ray hits

	// Rectnagles
	for (auto& rectangle : rectangleTable) {
		// Test if inside rectangle, if not go to next rectangle
		if (rectangle.rayIntersection(ray, minDistance)) break;
	}

	// Go through all triangles
	for (auto& triangle : triangleTable) {
		if (triangle.rayIntersection(ray, minDistance)) break;
	}

	// Go through all spheres
	for (auto& sphere : sphereTable) {
		if (sphere.rayIntersection(ray, minDistance)) break;
	}

	// Go trhrough all tetrahedrons
	for (auto& tetra : tetrahedronTable) {
		tetra.rayIntersection(ray, minDistance);
	}

	// Handle the different kind of reflections, Lambertian, Mirror, Transparent
	if (ray.getRayType() != RayType::SHADOW) handleReflection(ray, numReflections);
}

// Handle different kind of reflections (Lambertian, Mirror, Transparent) on dirrefent Polygons
void Scene::handleReflection(Ray& ray, int numReflections) {
	// Do different things depending on material
	switch (ray.getObjectMaterial()) {
		// Mirror, reflect ray and cast it again
	case Material::MIRROR: {
		glm::vec3 normal = ray.getObjectNormal(); // Normal for the polygon
		// Reflected direction
		glm::vec3 newDirection = ray.getDirection() - 2.0f * glm::dot(ray.getDirection(), normal) * normal;

		Ray newRay{ ray.getEndpoint(), newDirection };

		// Set up doubly linked list
		ray.nextRay = &newRay;
		newRay.prevRay = &ray;

		// Recursively cast ray into scene again until a non mirror is hit
		// Continue to cast ray with 99 % probability, to avoid stack overflow with "infinite mirror"
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
		break;
	}
	// Lambertian surface, cast ray to the light source and indirect light
	case Material::LAMBERTIAN: {
		// Get the light % for direct light
		ColorDBL directLight = this->directLight(ray);

		// Get the indirect light
		ColorDBL indirectLight = this->indirectLight(ray);
		ray.setColor(indirectLight + directLight);
		break;
	}
	// Transparent surface
	case Material::TRANSPARENT: {
		glm::vec3 normal = glm::normalize(ray.getObjectNormal()); // Normal for the polygon
		glm::vec3 ingoingRayDirection = glm::normalize(ray.getDirection()); // Normalised inclination angle Omega

		float n1 = 1.0f; // Air
		float n2 = 1.5f; // Glass

		// Schlick's law for BRDF
		float R0 = (float)glm::pow((n2 - n1) / (n1 + n2), 2);
		float reflectedBRDF = R0 + (1.0f - R0) * (float)glm::pow(1.0f - glm::cos(glm::dot(-ingoingRayDirection, normal)), 5);

		if (ray.getRayType() == RayType::INSIDE_TRANSPARENT) {
			normal = -normal; // Invert normal since we are inside the sphere

			// Test if we have total internal reflection
			// Total reflection, only calculate reflected ray
			if (glm::sin(glm::dot(ingoingRayDirection, normal) * n1 / n2) > 1.0f) {
				reflectRay(ray);
				break;
			}

			// Reflect ray, not refract
			if (distribution(seed) < reflectedBRDF) {
				reflectRay(ray);
			}
			// Refract ray, not reflect
			else {
				float R = n2 / n1; // SinB / SinOmega, ratio of refractive index
				refractRay(ray, R);
			}
			break;
		}


		R0 = (float)glm::pow((n1 - n2) / (n1 + n2), 2);
		reflectedBRDF = R0 + (1.0f - R0) * (float)glm::pow(1.0f - glm::cos(glm::dot(-ingoingRayDirection, normal)), 5);

		// Reflect ray, not refract
		if (distribution(seed) < reflectedBRDF) {
			reflectRay(ray);
		}
		// Refract ray, not reflect
		else {
			float R = n1 / n2; // SinB / SinOmega, ratio of refractive index
			refractRay(ray, R);
		}
		
		break;
	}
	// Light source
	case Material::LIGHT: {
		ray.setColor(ColorDBL(1.0f, 1.0f, 1.0f));
		break;
	}
	default:
		break;
	}
}

// Get the direct light from light source to a specific point
ColorDBL Scene::directLight(const Ray& ray) {
	// Define area light
	glm::vec3 v0 = vertexTable[12]; // glm::vec3(5.0f, 0.0f, 5.0f);
	glm::vec3 v1 = vertexTable[13]; // glm::vec3(6.0f, 0.0f, 5.0f);
	glm::vec3 v2 = vertexTable[14]; // glm::vec3(6.0f, 0.1f, 5.0f);
	glm::vec3 v3 = vertexTable[15]; // glm::vec3(5.0f, 0.1f, 5.0f);

	glm::vec3 e1 = v2 - v1;
	glm::vec3 e2 = v0 - v1;

	glm::vec3 lightNormal = glm::normalize(glm::cross(e1, e2));

	glm::vec3 surfaceNormal = ray.getObjectNormal();
	float lightChannel = 0.0f; // Amount of light at each colour channel
	for (int i = 0; i < NUMBER_OF_SHADOW_RAYS; ++i) {
		// Create two random parameter variables, uniform distribution
		float s = distribution(seed);
		float t = distribution(seed);

		glm::vec3 lightPoint = v1 + s * e1 + t * e2; // Random point on the light source
		glm::vec3 rayLightDistanceVector = lightPoint - ray.getEndpoint(); // d_i

		float cosX = glm::dot(lightNormal, rayLightDistanceVector) / glm::length(rayLightDistanceVector);
		float cosY = -glm::dot(surfaceNormal, rayLightDistanceVector) / glm::length(rayLightDistanceVector);

		// Create a shadow ray to cast towards the light source to see if there is something in between
		Ray shadowRay = Ray(ray.getEndpoint(), glm::normalize(rayLightDistanceVector), RayType::SHADOW);
		castRay(shadowRay);
		float shadowRayLength = glm::length(shadowRay.getEndpoint() - shadowRay.getStartpoint());

		//bool V_xy = (abs(shadowRayLength - glm::length(rayLightDistanceVector)) < COMPARE_ELLIPSE);
		float V_xy = 1.0;

		if (shadowRayLength < glm::length(rayLightDistanceVector)) {
			V_xy = 0.0;
		}

		lightChannel += glm::max(0.0f, cosX * cosY / (float)glm::pow(glm::length(rayLightDistanceVector), 2)) * V_xy;
	}

	const float BRDF = 1.0f / M_PI;

	ColorDBL lightColor = ColorDBL(lightChannel, lightChannel, lightChannel); // Combine colour channels (RGB) to a ColorDBL
	lightColor = lightColor * ray.getColor() * (glm::length(glm::cross(e1, e2))  * 32.0f * BRDF * 1.0f / NUMBER_OF_SHADOW_RAYS); // Scale light colour in terms of Area, Watt
	
	return lightColor;
}

// Get the indirect light from other surfaces
ColorDBL Scene::indirectLight(const Ray& ray) {

	// Perform Russian roulette to decide if to continue, using Rho as probability of surviving
	float random = distribution(seed);
	// if (random > ray.getPolygon()->getRho()) return ColorDBL(); // If not to continue ray path
	if (random < 0.25f) return ColorDBL(); // Temp from above

	glm::vec3 surfaceNormal = ray.getObjectNormal();

	// Random direction in local hemisphere with nonuniform distribution, reuse random variable
	float randomPhi = 1.0f - random;
	float randomOmega = glm::acos(glm::sqrt(1.0f - random));

	// Set up orthogonal local coordinate system
	glm::vec3 ey;
	glm::vec3 ez;
	createLocalCartesianCoordinateSystem(surfaceNormal, ey, ez);

	// Get intersection with hemisphere in local cartesian coordinates
	float x0 = glm::cos(randomPhi) * glm::sin(randomOmega);
	float y0 = glm::sin(randomPhi) * glm::sin(randomOmega);
	float z0 = glm::cos(randomOmega);

	// Convert to global coordinate system
	glm::vec3 globalIntersectionPoint = glm::vec3(
		x0 * surfaceNormal.x + y0 * ey.x + z0 * ez.x,
		x0 * surfaceNormal.y + y0 * ey.y + z0 * ez.y,
		x0 * surfaceNormal.z + y0 * ey.z + z0 * ez.z);

	glm::vec3 rayPosition = ray.getEndpoint();
	Ray reflectionRay{rayPosition, globalIntersectionPoint - rayPosition};
	castRay(reflectionRay);


	return reflectionRay.getColor() * ray.getColor() * 0.6f;
}

// Create a local coordinate system with orthogonal axes
void Scene::createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const {
	// Make e2 and e3 orthogonal to e3 and each other, and normalise
	e2 = glm::vec3(e1.z, 0.0f, -e1.x);
	e3 = glm::cross(e1, e2);
}

// Calculate the reflected ray, cast it and set its colour
void Scene::reflectRay(Ray& ray) {
	glm::vec3 normal = glm::normalize(ray.getObjectNormal()); // Normal for the polygon
	glm::vec3 ingoingRayDirection = glm::normalize(ray.getDirection()); // Normalised inclination angle Omega
	RayType reflectedRayType = RayType::INSIDE_TRANSPARENT;

	if (ray.getRayType() == RayType::INSIDE_TRANSPARENT) {
		// Ray is inside object, need to reverse the normal and the reflected ray will not be inside
		normal = -normal;
		reflectedRayType = RayType::PRIMARY;
	}

	// Reflected direction
	glm::vec3 reflectedDirection = ray.getDirection() - 2.0f * glm::dot(ray.getDirection(), normal) * normal;

	// Create reflected ray, with margin to not get stuck
	Ray reflectedRay = Ray(ray.getEndpoint() - normal * 0.002f, reflectedDirection, reflectedRayType);

	// Set up doubly linked list
	ray.nextRay = &reflectedRay;
	reflectedRay.prevRay = &ray;

	// Recursively cast reflected ray into scene
	castRay(reflectedRay);

	reflectedRay.prevRay->setColor(reflectedRay.getColor());
}

// Calculate the refracted ray, cast it and set its colour
void Scene::refractRay(Ray& ray, float R) {
	glm::vec3 normal = glm::normalize(ray.getObjectNormal()); // Normal for the polygon
	glm::vec3 ingoingRayDirection = glm::normalize(ray.getDirection()); // Normalised inclination angle Omega
	RayType refractedRayType = RayType::INSIDE_TRANSPARENT;

	if (ray.getRayType() == RayType::INSIDE_TRANSPARENT) {
		// Ray is inside object, need to reverse the normal and the refracted ray will not be inside
		normal = -normal;
		refractedRayType = RayType::PRIMARY;
	}

	// Reflected direction
	glm::vec3 refractedDirection = R * ingoingRayDirection + normal * (float)(-R * glm::dot(normal, ingoingRayDirection) - glm::sqrt(1.0f - R * R * (1.0f - glm::pow(glm::dot(normal, ingoingRayDirection), 2))));

	// Create refracted ray, with margin to not get stuck
	Ray refractedRay = Ray(ray.getEndpoint() - normal * 0.002f, refractedDirection, refractedRayType);

	// Set up doubly linked list
	ray.nextRay = &refractedRay;
	refractedRay.prevRay = &ray;

	// Recursively cast refracted ray into scene
	castRay(refractedRay);

	refractedRay.prevRay->setColor(refractedRay.getColor());
}