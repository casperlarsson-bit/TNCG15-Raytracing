#include "../include/ColorDBL.h"


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