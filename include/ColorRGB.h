#pragma once

class ColorRGB {

	// Default constructor, 0 0 0
	ColorRGB();

	// Constructor to create a colour of values
	ColorRGB(double r, double g, double b);



private:
	double red;
	double green;
	double blue;
};