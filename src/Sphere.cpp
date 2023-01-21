/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#include "../include/Sphere.h"
#include <iostream>
#include <math.h>

#define M_PI 3.14159265358979323846f  // Pi

// Default constructor
Sphere::Sphere() {
	radius = 1.0f;
	centreVertex = glm::vec3(0.0f, 0.0f, 0.0f);
	color = ColorDBL();
	material = Material::LAMBERTIAN;
}

// Value constructor
Sphere::Sphere(float _radius, glm::vec3 _centreVertex, ColorDBL _color, Material _material) {
	radius = _radius;
	centreVertex = _centreVertex;
	color = _color;
	material = _material;
}

// Calculate the intersection of a ray and the surface
// Return true if hits the surface
// Hits circle 0, 1 or 2 times. Want the first hit. Assume 1 hit = 0 hits
bool Sphere::rayIntersection(Ray& ray, float& minDistance) const {
	glm::vec3 rayStart = ray.getStartpoint();
	glm::vec3 rayDirection = glm::normalize(ray.getDirection());

	glm::vec3 x_i; // Intersection point

	// Get parameters for quadratic equation
	float c1 = glm::dot(rayDirection, rayDirection);
	float c2 = 2.0f * glm::dot(rayDirection, rayStart - centreVertex);
	float c3 = glm::dot(rayStart - centreVertex, rayStart - centreVertex) - radius * radius;

	// Arg is the value under square root
	float arg = c2 * c2 - 4.0f * c1 * c3;

	// Ray misses Sphere
	if (arg < 0.0f) return false;

	// One solution, touches the side
	if (arg < COMPARE_ELLIPSE) {
		float t = -c2 / (2.0f * c1);
		x_i = rayStart + rayDirection * t;
	}

	// Time parameter for ray intersection, two possible solutions
	float t1 = (-c2 + glm::sqrt(arg)) / (2.0f * c1);
	float t2 = (-c2 - glm::sqrt(arg)) / (2.0f * c1);

	// Take the parameter of the non negative solution, if any
	if (t2 > 0.0f) {
		x_i = rayStart + rayDirection * t2;
	}
	else if (t1 > 0.0f) {
		x_i = rayStart + rayDirection * t1;
	}
	else {
		return false;
	}

	if (glm::length(x_i - ray.getStartpoint()) < minDistance) {
		// Set the ray colour either to the colour of the rectangle or load from texture
		if (filename == "") {
			ray.setColor(color);
		}
		else {
			glm::vec3 pointToCentre = glm::normalize(centreVertex - x_i);

			// Calculate (u,v) texture coordinates
			// https://en.wikipedia.org/wiki/UV_mapping#UV_unwrapping
			float u = 0.5 + atan2(pointToCentre.y, pointToCentre.x) / (2 * M_PI);
			float v = 0.5 + glm::asin(pointToCentre.z) / M_PI;

			int x = std::min((int)(u * textureWidth), textureWidth - 1);
			int y = std::min((int)(v * textureHeight), textureHeight - 1);

			const size_t RGBA = 4;
			size_t index = RGBA * (y * textureWidth + x);

			int R = static_cast<int>(texture[index + 0]);
			int G = static_cast<int>(texture[index + 1]);
			int B = static_cast<int>(texture[index + 2]);

			ray.setColor(ColorDBL(R, G, B));
		}

		ray.setEndVertex(x_i + glm::normalize(x_i - centreVertex) * 0.001f);
		ray.setObjectNormal(glm::normalize(x_i - centreVertex));
		ray.setObjectMaterial(getMaterial());
		minDistance = glm::length(x_i - ray.getStartpoint());
		return true;
	}

	return false;
}

// Get what material the Sphere is made of
Material Sphere::getMaterial() const {
	return material;
}

// Sets the material of the Sphere
void Sphere::setMaterial(Material _material) {
	material = _material;
}

// Get the colour of the Sphere
ColorDBL Sphere::getColor() const {
	return color;
}

// Set the colour of the Sphere
void Sphere::setColor(ColorDBL _color) {
	color = _color;
}

// Set up the file to the texture
void Sphere::setTexture(std::string filepath) {
	filename = filepath;

	// Load texture into vector and get width and height
	bool success = load_image(texture, filename, textureWidth, textureHeight);
	if (!success)
	{
		// If file could not be opened, terminate program
		std::cout << "Error loading texture \"" << filepath << "\"\nMake sure you spelled the filepath correctly and that the file exists in that folder.\n";
		exit(EXIT_SUCCESS);
	}
}

// Get the centre of the sphere
glm::vec3 Sphere::getCentre() const {
	return centreVertex;
}