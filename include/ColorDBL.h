/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once

class ColorDBL {
public:
	// Default constructor, 0 0 0
	ColorDBL();

	// Constructor to create a colour of values
	ColorDBL(float _r, float _g, float _b);

	// Overloaded operator*, scales the colour by value
	// To make colour darker/brighter
	ColorDBL operator*(float value) const;

	// Overloaded operator* to multiply two colours
	// Multiply each colour channel
	ColorDBL operator*(ColorDBL color) const;

	// Overloaded operator+ to add two colours channel by channel
	ColorDBL operator+(ColorDBL color) const;

	// Add color
	ColorDBL& operator+=(const ColorDBL& color);

	float red;
	float green;
	float blue;
private:
};