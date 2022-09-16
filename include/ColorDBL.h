#pragma once

class ColorDBL {
public:
	// Default constructor, 0 0 0
	ColorDBL();

	// Constructor to create a colour of values
	ColorDBL(double _r, double _g, double _b);

	// Overloaded operator*, scales the colour by value
	// To make colour darker/brighter
	ColorDBL operator*(double value) const;

	double red;
	double green;
	double blue;
private:
};