#pragma once

#include "ColorRGB.h"
#include "glm/glm.hpp"

class Ray {
public:
	// Default constructor
	Ray();

	// Destructor
	~Ray();

	//// Class Member Functions
	
	// Get the current Color of the ray
	ColorRGB getColor();

	// Set the Color of the ray
	void setColor(ColorRGB rgb);
	
private:
	glm::vec4 startingPoint;
	glm::vec4 endPoint;
	glm::vec3 direction;

	Ray* prevRay;
	Ray* nextRay;
	// Surface* startingVertex; // Implement Surface?

	ColorRGB rayColor;
};