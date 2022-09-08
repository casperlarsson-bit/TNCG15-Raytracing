#pragma once

class ColorDBL {
public:

	// Default constructor, 0 0 0
	ColorDBL();

	// Constructor to create a colour of values
	ColorDBL(double r, double g, double b);

	double red;
	double green;
	double blue;
private:
};