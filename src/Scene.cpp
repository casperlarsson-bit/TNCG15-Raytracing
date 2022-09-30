#include "../include/Scene.h"
#include "../include/glm/glm.hpp"
#include <iostream>
#include <math.h>
#include <random> // Default random engine

#define M_PI 3.14159265358979323846  // Pi

// Should replace above function
std::default_random_engine seed;
std::uniform_real_distribution<double> distribution(0.0, 1.0);


const int RANDOM_REFLECTION = 99; // Percentage to continue cast rays in mirror, remove this
const double MIRROR_VALUE = 0.95; // How much darker the light should be when returned from a mirror
const int NUMBER_OF_SHADOW_RAYS = 3;

// Default constructor to setup everything for the scene (Vertextable, Polygons etc.)
Scene::Scene() {
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
	rectangleTable[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	rectangleTable[1].setColor(ColorDBL(0.1, 0.1, 0.1));
	rectangleTable[2].setColor(ColorDBL(0.2, 0.66, 0.32));
	rectangleTable[3].setColor(ColorDBL(0.66, 0.62, 0.2));
	// rectangleTable[3].setMaterial(Material::MIRROR);
	rectangleTable[4].setColor(ColorDBL(0.2, 0.27, 0.66));
	rectangleTable[5].setColor(ColorDBL(0.66, 0.2, 0.2));
	rectangleTable[6].setColor(ColorDBL(0.2, 0.63, 0.66));
	// rectangleTable[6].setMaterial(Material::MIRROR);
	rectangleTable[7].setColor(ColorDBL(0.43, 0.2, 0.66));

	triangleTable[0].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangleTable[1].setColor(ColorDBL(0.8, 0.8, 0.8));
	triangleTable[2].setColor(ColorDBL(0.1, 0.1, 0.1));
	triangleTable[3].setColor(ColorDBL(0.1, 0.1, 0.1));

	// Spheres in the scene
	sphereTable[0] = Sphere(1.0, glm::vec4(6, 1, -1, 1), ColorDBL(1, 0, 1), Material::MIRROR);
	sphereTable[1] = Sphere(0.8, glm::vec4(4, -3, -2, 1), ColorDBL(1, 0, 1), Material::TRANSPARENT);

	// Tetrahedron in the scene
	tetrahedronTable[0] = Tetrahedron(glm::vec3(8, -1, -3), ColorDBL(0.16, 0.04, 0.32), Material::LAMBERTIAN);
}

// Cast and trace a ray
void Scene::castRay(Ray& ray, int numReflections) {
	// Rectnagles
	for (auto& rect : rectangleTable) {
		ray.setEndVertex(rect.rayIntersection(ray));
		// Test if inside rectangle, if not go to next rectangle
		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Handle the different kind of reflections, Lambertian, Mirror, Transparent
		if (ray.getRayType() != RayType::SHADOW) handleReflection(ray, rect, numReflections);
		break;
	}

	// Go through all triangles
	for (auto& tri : triangleTable) {
		ray.setEndVertex(tri.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Handle the different kind of reflections, Lambertian, Mirror, Transparent
		if (ray.getRayType() != RayType::SHADOW) handleReflection(ray, tri, numReflections);
		break;
	}

	// Go through all spheres
	for (auto& circle : sphereTable) {
		ray.setEndVertex(circle.rayIntersection(ray));

		if (ray.getEndpoint()[0] == NULL) {
			continue;
		}

		// Handle the different kind of reflections, Lambertian, Mirror, Transparent
		if (ray.getRayType() != RayType::SHADOW) handleReflection(ray, circle, numReflections);
		break;
	}

	// Go trhrough all tetrahedrons
	for (auto& tetra : tetrahedronTable) {
		// Go through the triangles in the tetrahedron
		for (auto& tri : tetra.triangleTable) {
			ray.setEndVertex(tri.rayIntersection(ray));

			if (ray.getEndpoint()[0] == NULL) {
				continue;
			}

			// Handle the different kind of reflections, Lambertian, Mirror, Transparent
			if (ray.getRayType() != RayType::SHADOW) handleReflection(ray, tri, numReflections);
			break;
		}
	}
}

// Handle different kind of reflections (Lambertian, Mirror, Transparent) on dirrefent Polygons
void Scene::handleReflection(Ray& ray, Polygon& polygon, int numReflections) {
	ray.rayPolygonIntersection = &polygon;

	// Do different things depending on material of rectangle
	switch (polygon.getMaterial()) {
		// Mirror, reflect ray and cast it again
	case Material::MIRROR: {
		// Reflected direction
		glm::vec3 newDirection = ray.getDirection() - (float)2 * glm::dot(ray.getDirection(), polygon.getNormal()) * polygon.getNormal();

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
			int randomReflection = (int)(distribution(seed) * 100);
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
		ray.setColor((indirectLight + directLight) * polygon.getColor());
		break;
	}
	case Material::TRANSPARENT: {
		break;
	}
	default:
		break;
	}
}

// Overloaded handleReflection to do the same thing but for Spheres, since the normal is computed in a different way
void Scene::handleReflection(Ray& ray, Sphere& sphere, int numReflections) {
	// Do different things depending on material of rectangle
	switch (sphere.getMaterial()) {
		// Mirror, reflect ray and cast it again
	case Material::MIRROR: {
		glm::vec3 normal = glm::vec3(ray.getEndpoint() - sphere.getCentre()); // Normal for the sphere
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
		break;
	}
	// Lambertian surface, cast ray to the light source and indirect light
	case Material::LAMBERTIAN: {
		// Get the light % for direct light
		ColorDBL directLight = this->directLight(ray);

		// Get the indirect light
		ColorDBL indirectLight = this->indirectLight(ray);
		ray.setColor((indirectLight + directLight) * sphere.getColor());
		break;
	}
	// Transparent surface
	case Material::TRANSPARENT: {
		glm::vec3 sphereNormal = glm::normalize(glm::vec3(ray.getEndpoint() - sphere.getCentre())); // Normal for the sphere
		glm::vec3 ingoingRayDirection = glm::normalize(ray.getDirection()); // Normalised inclination angle Omega

		double n1 = 1.0; // Air
		double n2 = 1.5; // Glass

		// Schlick's law for BRDF
		double R0 = glm::pow((n1 - n2) / (n1 + n2), 2);
		double reflectedBRDF = R0 + (1.0 - R0) * glm::pow(1.0 - glm::cos(glm::dot(ingoingRayDirection, sphereNormal)), 5);
		//double transmittedBRDF = 1.0 - reflectedBRDF; // Unnecessary?

		if (ray.getRayType() == RayType::INSIDE_TRANSPARENT) {
			sphereNormal = -sphereNormal; // Invert normal since we are inside the sphere

			// Test if we have total reflection
			// Total reflection, only calculate reflected ray
			if (glm::sin(glm::dot(ingoingRayDirection, sphereNormal) * n1 / n2) > 1) {
				// Reflected direction
				glm::vec3 reflectedDirection = ray.getDirection() - (float)2 * glm::dot(ray.getDirection(), sphereNormal) * sphereNormal;

				Ray reflectedRay = Ray(ray.getEndpoint(), reflectedDirection);

				// Set up doubly linked list
				ray.nextRay = &reflectedRay;
				reflectedRay.prevRay = &ray;

				// Recursively cast reflected ray into scene
				castRay(reflectedRay);

				reflectedRay.prevRay->setColor(reflectedRay.getColor());

				break;
			}

			// Not total reflection, calculate in the same way as if from outside sphere
			// Normal is inverted already
		}
		
		// Reflect ray, not refract
		if (distribution(seed) < reflectedBRDF) {
			// Reflected direction
			glm::vec3 reflectedDirection = ray.getDirection() - (float)2 * glm::dot(ray.getDirection(), sphereNormal) * sphereNormal;
				
			Ray reflectedRay = Ray(ray.getEndpoint(), reflectedDirection);

			// Set up doubly linked list
			ray.nextRay = &reflectedRay;
			reflectedRay.prevRay = &ray;

			// Recursively cast reflected ray into scene
			castRay(reflectedRay); 

			reflectedRay.prevRay->setColor(reflectedRay.getColor());
		}
		// Refract ray, not reflect
		else {
			double R = n1 / n2; // SinB / SinOmega, ratio of refractive index
			// Reflected direction
			glm::vec3 refractedDirection = (float)R * ingoingRayDirection + sphereNormal * (float)(-R * glm::dot(sphereNormal, ingoingRayDirection) - glm::sqrt(1 - R * R * (1 - glm::pow(glm::dot(sphereNormal, ingoingRayDirection), 2))));

			Ray refractedRay = Ray(ray.getEndpoint(), refractedDirection, RayType::INSIDE_TRANSPARENT);

			// Set up doubly linked list
			ray.nextRay = &refractedRay;
			refractedRay.prevRay = &ray;

			// Recursively cast refracted ray into scene
			castRay(refractedRay);

			refractedRay.prevRay->setColor(refractedRay.getColor());
		}
		
		break;
	}
	default:
		break;
	}
}

// Get the direct light from light source to a specific point
ColorDBL Scene::directLight(const Ray& ray) {
	// Define area light
	glm::vec4 v0 = glm::vec4(5, 0, 5, 1);
	glm::vec4 v1 = glm::vec4(5.1, 0, 5, 1);
	glm::vec4 v2 = glm::vec4(5.1, 0.1, 5, 1);
	glm::vec4 v3 = glm::vec4(5, 0.1, 5, 1);

	glm::vec4 e1 = v2 - v1;
	glm::vec4 e2 = v0 - v1;

	glm::vec3 lightNormal = glm::normalize(glm::cross(glm::vec3(e2), glm::vec3(e1)));

	glm::vec3 surfaceNormal = ray.getPolygon()->getNormal();
	double lightChannel = 0; // Amount of light at each colour channel
	for (int i = 0; i < NUMBER_OF_SHADOW_RAYS; ++i) {
		// Create two random parameter variables, uniform distribution
		double s = distribution(seed);
		double t = distribution(seed);

		glm::vec4 lightPoint = v1 + (float)s * e1 + (float)t * e2; // Random point on the light source
		glm::vec3 rayLightDistanceVector = glm::vec3(lightPoint - ray.getEndpoint()); // d_i

		double cosX = glm::dot(lightNormal, rayLightDistanceVector) / glm::length(rayLightDistanceVector);
		double cosY = -glm::dot(surfaceNormal, rayLightDistanceVector) / glm::length(rayLightDistanceVector);

		Ray shadowRay = Ray(ray.getEndpoint(), glm::normalize(rayLightDistanceVector), RayType::SHADOW);
		castRay(shadowRay);
		double shadowRayLength = glm::length(shadowRay.getEndpoint() - shadowRay.getStartpoint());

		bool V_xy = !(abs(shadowRayLength - glm::length(rayLightDistanceVector) < COMPARE_ELLIPSE));

		lightChannel +=  glm::max((double)0, cosX * cosY / std::pow(glm::length(rayLightDistanceVector), 2)) * V_xy;
	}

	const double BRDF = 1 / M_PI;

	ColorDBL lightColor = ColorDBL(lightChannel, lightChannel, lightChannel); // Combine colour channels (RGB) to a ColorDBL
	lightColor = lightColor * (glm::length(glm::cross(glm::vec3(e1), glm::vec3(e2))) * 3200 * BRDF * 1 / NUMBER_OF_SHADOW_RAYS); // Scale light colour in terms of Area, Watt
	
	return lightColor;
}

// Get the indirect light from other surfaces
ColorDBL Scene::indirectLight(const Ray& ray) {

	// Perform Russian roulette to decide if to continue, using Rho as probability of surviving
	double random = distribution(seed);
	if (random > ray.getPolygon()->getRho()) return ColorDBL(); // If not to continue ray path

	glm::vec3 surfaceNormal = ray.getPolygon()->getNormal();

	// Random direction in local hemisphere with nonuniform distribution, reuse random variable
	double randomPhi = 1 - random;
	double randomOmega = glm::acos(glm::sqrt(1.0 - random));

	// Set up orthogonal local coordinate system
	glm::vec3 ey;
	glm::vec3 ez;
	createLocalCartesianCoordinateSystem(surfaceNormal, ey, ez);

	// Get intersection with hemisphere in local cartesian coordinates
	double x0 = glm::cos(randomPhi) * glm::sin(randomOmega);
	double y0 = glm::sin(randomPhi) * glm::sin(randomOmega);
	double z0 = glm::cos(randomOmega);

	// Convert to global coordinate system
	glm::vec4 globalIntersectionPoint = glm::vec4(
		x0 * surfaceNormal.x + y0 * ey.x + z0 * ez.x,
		x0 * surfaceNormal.y + y0 * ey.y + z0 * ez.y,
		x0 * surfaceNormal.z + y0 * ey.z + z0 * ez.z,
		1.0);

	glm::vec4 rayPosition = ray.getEndpoint();
	Ray reflectionRay{rayPosition, glm::vec3(globalIntersectionPoint - rayPosition)};
	castRay(reflectionRay);


	return reflectionRay.getColor() *ray.getColor() * 0.6;
}

// Create a local coordinate system with orthogonal axes
void Scene::createLocalCartesianCoordinateSystem(glm::vec3 e1, glm::vec3& e2, glm::vec3& e3) const {
	// Make e2 and e3 orthogonal to e3 and each other, and normalise
	e2 = glm::vec3(e1.z, 0, -e1.x);
	e3 = glm::cross(e1, e2);
}