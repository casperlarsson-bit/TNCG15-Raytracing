#include "ColorRGB.h"


// Default constructor, 0 0 0
ColorRGB::ColorRGB() {
	red = 0;
	green = 0;
	blue = 0;
}

// Constructor to create a colour of values
ColorRGB::ColorRGB(double r, double g, double b) {
	red = r;
	green = g;
	blue = b;
}