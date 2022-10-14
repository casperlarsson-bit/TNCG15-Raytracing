#pragma once

#include "ColorDBL.h"
#include "Material.h"
#include "glm/glm.hpp"

// Forward declaration https://stackoverflow.com/questions/8526819/c-header-files-including-each-other-mutually
class Polygon;

class Ray {
public:
	// Default constructor
	Ray();

	// Constructor which sets starting position and direction
	Ray(glm::vec4 _startPosition, glm::vec3 _direction, RayType _rayType = RayType::PRIMARY);

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

	// Set the normal of the object the ray intersected with
	void setObjectNormal(glm::vec3 _normal);

	// Set the material of the object the ray intersected with
	void setObjectMaterial(Material _material);

	// Get the normal of the object the ray intersected with
	glm::vec3 getObjectNormal() const;

	// Get the material of the object the ray intersected with
	Material getObjectMaterial() const;

	// Get startpoint of Ray
	glm::vec4 getStartpoint() const;

	// Get endpoint of Ray
	glm::vec4 getEndpoint() const;

	// Get direction of Ray
	glm::vec3 getDirection() const;

	// Get the Polygon which the Ray intersected with
	Polygon* getPolygon() const;

	// Get the type of ray (shadow, primary etc.)
	RayType getRayType() const;

	Ray* prevRay;
	Ray* nextRay;
	Polygon* rayPolygonIntersection;
private:
	glm::vec4 startVertice;
	glm::vec4 endVertice;
	glm::vec3 direction;

	RayType rayType;
	ColorDBL rayColor;
	glm::vec3 objectNormal;
	Material objectMaterial;
};