#include "Ray.h"


// Default constructor
Ray::Ray() = default;

// Destructor
Ray::~Ray() = default;

//// Class Member Functions

// Get the current Color of the ray
ColorRGB Ray::getColor() {
	return this->rayColor;
}

// Set the Color of the ray
void Ray::setColor(ColorRGB rgb) {
	rayColor = rgb;
}
