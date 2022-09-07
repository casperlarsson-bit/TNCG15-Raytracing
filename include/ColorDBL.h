#pragma once

class ColorDBL {

	// Default constructor, 0 0 0
	ColorDBL();

	// Constructor to create a colour of values
	ColorDBL(double r, double g, double b);



private:
	double red;
	double green;
	double blue;
};