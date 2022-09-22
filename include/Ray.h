#pragma once

#include "ColorDBL.h"
#include "glm/glm.hpp"

class Ray {
public:
	// Default constructor
	Ray();

	// Constructor which sets starting position and direction
	Ray(glm::vec4 _startPosition, glm::vec3 _direction);

	// Destructor
	~Ray();

	//// Class Member Functions

	// Get the current Color of the ray
	ColorDBL getColor() const;

	// Set the Color of the ray with ColorDBL
	void setColor(ColorDBL _rgb);

	// Set the Color of the ray with doubles
	void setColor(double _red, double _green, double _blue);

	// Set the direction of a Ray
	void setDirection(glm::vec3 _direction);

	// Set the end vertex of the ray
	void setEndVertex(glm::vec4 _endVertex);

	// Get startpoint of Ray
	glm::vec4 getStartpoint() const;

	// Get endpoint of Ray
	glm::vec4 getEndpoint() const;

	// Get direction of Ray
	glm::vec3 getDirection() const;

	Ray* prevRay;
	Ray* nextRay;
private:
	glm::vec4 startVertice;
	glm::vec4 endVertice;
	glm::vec3 direction;

	//Polygon* startingVertex;

	ColorDBL rayColor;
};