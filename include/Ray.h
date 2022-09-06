#pragma once

#include "ColorRGB.h"
#include "glm/glm.hpp"

class Ray {
public:
	// Default constructor
	Ray();

	// Destructor
	~Ray();


private:
	glm::vec4 startingPoint; // Need to implement vertex/vector?
	glm::vec4 endPoint;
	glm::vec3 direction;

	Ray* prevRay;
	Ray* nextRay;
	// Surface* startingVertex; // Implement Surface?

	ColorRGB rayColor;
};