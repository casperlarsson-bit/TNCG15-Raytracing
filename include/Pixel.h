#pragma once

#include "ColorDBL.h"

class Pixel {
public:
	// Default constructor
	Pixel();

	// Create pixel with colour
	Pixel(ColorDBL _color);

	// Get colour of the pixel
	ColorDBL getColor() const;

	// Set the colour of the pixel, with double values
	void setColor(double _r, double _g, double _b);

	// Set the colour of the pixel, with ColorDBL
	void setColor(ColorDBL _color);

private:
	ColorDBL color;
};