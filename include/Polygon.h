/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Ray.h"
#include "Material.h"
#include "functions.h"

const float COMPARE_ELLIPSE = 0.00001f;

class Polygon {
public:

	// Default constructor
	Polygon();

	// Value constructor
	Polygon(ColorDBL _color, glm::vec3 _normal, Material _material);

	// Compute the normal of the Polygon. Normal points into the room
	glm::vec3 getNormal() const;

	// Calculate the normal automatically from the vertices
	virtual void calculateNormal() = 0;

	// Get the colour of the Polygon
	ColorDBL getColor() const;

	// Set the colour of the Polygon, and update rho
	void setColor(ColorDBL _color);

	// Calculate the intersection of a ray and the surface
	// Return true if hits the surface
	// Done in sub classes
	virtual bool rayIntersection(Ray &ray, float& minDistance) const = 0;

	// Get what material the Polygon is made of
	Material getMaterial() const;

	// Sets the material of the Polygon
	void setMaterial(Material _material);

	// Set up the file to the texture
	void setTexture(std::string filepath);

	// Get the Lambertian rho
	float getRho() const;

	ColorDBL color;
	glm::vec3 normal;

	std::vector<unsigned char> texture;
	int textureWidth = 0;
	int textureHeight = 0;
	std::string filename = "";
private:
	Material material;
	float rho;
};