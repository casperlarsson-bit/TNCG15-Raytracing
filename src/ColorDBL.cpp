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