#pragma once


class Ray {
public:
	// Default constructor
	Ray();

	// Destructor
	~Ray();

	//// Class Member Functions

	// Get the current Color of the ray


private:
	int test = 10;

	Ray* prevRay;
	Ray* nextRay;
	// Surface* startingVertex; // Implement Surface?

	// ColorRGB rayColor;
};