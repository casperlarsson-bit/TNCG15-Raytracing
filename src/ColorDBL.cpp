#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"


// Default constructor, 0 0 0
ColorDBL::ColorDBL() {
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
}

// Constructor to create a colour of values
ColorDBL::ColorDBL(float _r, float _g, float _b) {
	red = _r;
	green = _g;
	blue = _b;
}

// Overloaded operator*, scales the colour by value
// To make colour darker/brighter
ColorDBL ColorDBL::operator*(float value) const {
	return ColorDBL(red * value, green * value, blue * value);
}

// Overloaded operator* to multiply two colours
	// Multiply each colour channel
ColorDBL ColorDBL::operator*(ColorDBL color) const {
	return ColorDBL(red * color.red, green * color.green, blue * color.blue);
}

// Overloaded operator+ to add two colours channel by channel
ColorDBL ColorDBL::operator+(ColorDBL color) const {
	float newRed = glm::min(1.0f, red + color.red);
	float newGreen = glm::min(1.0f, green + color.green);
	float newBlue = glm::min(1.0f, blue + color.blue);


	return ColorDBL(newRed, newGreen, newBlue);
}

// Add color
ColorDBL& ColorDBL::operator+=(const ColorDBL& color) {
	red += color.red;
	green += color.green;
	blue += color.blue;

	return *this;
}