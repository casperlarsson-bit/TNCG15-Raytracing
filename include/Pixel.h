/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

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

	// Set the colour of the pixel, with float values
	void setColor(float _r, float _g, float _b);

	// Set the colour of the pixel, with ColorDBL
	void setColor(ColorDBL _color);

private:
	ColorDBL color;
};