#pragma once

#include "../include/ColorDBL.h"

class Ray {
public:
	// Default constructor
	Ray();

	// Destructor
	~Ray();

	//// Class Member Functions

	// Get the current Color of the ray
	// ColorDBL getColor();


	// Set the Color of the ray
	//void setColor(ColorDBL rgb);

private:
	Ray* prevRay;
	Ray* nextRay;
	// Surface* startingVertex; // Implement Surface?

	// ColorDBL rayColor;
};