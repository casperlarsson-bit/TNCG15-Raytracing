#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"


// Default constructor, 0 0 0
ColorDBL::ColorDBL() {
	red = 0;
	green = 0;
	blue = 0;
}

// Constructor to create a colour of values
ColorDBL::ColorDBL(double _r, double _g, double _b) {
	red = _r;
	green = _g;
	blue = _b;
}

// Overloaded operator*, scales the colour by value
// To make colour darker/brighter
ColorDBL ColorDBL::operator*(double value) const {
	return ColorDBL(red * value, green * value, blue * value);
}

// Overloaded operator* to multiply two colours
	// Multiply each colour channel
ColorDBL ColorDBL::operator*(ColorDBL color) const {
	return ColorDBL(red * color.red, green * color.green, blue * color.blue);
}

// Overloaded operator+ to add two colours channel by channel
ColorDBL ColorDBL::operator+(ColorDBL color) const {
	double newRed = glm::min(1.0, red + color.red);
	double newGreen = glm::min(1.0, green + color.green);
	double newBlue = glm::min(1.0, blue + color.blue);


	return ColorDBL(newRed, newGreen, newBlue);
}