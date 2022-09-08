#pragma once

#include "ColorDBL.h"
#include "glm/glm.hpp"

class Ray {
public:
	// Default constructor
	Ray();

	// Destructor
	~Ray();

	//// Class Member Functions

	// Get the current Color of the ray
	ColorDBL getColor();

	// Set the Color of the ray with ColorDBL
	void setColor(ColorDBL _rgb);

	// Set the Color of the ray with doubles
	void setColor(double _red, double _green, double _blue);

	// Get startpoint of Ray
	glm::vec4 getStartpoint();

	// Get endpoint of Ray
	glm::vec4 getEndpoint();

	// Get direction of Ray
	glm::vec3 getDirection();

private:
	glm::vec4 startVertice;
	glm::vec4 endVertice;
	glm::vec3 direction;

	Ray* prevRay;
	Ray* nextRay;
	// Polygon* startingVertex;

	ColorDBL rayColor;
};