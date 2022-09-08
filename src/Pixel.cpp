#include "../include/Pixel.h"

// Default constructor
Pixel::Pixel() {

}

// Get colour of the pixel
ColorDBL Pixel::getColor() const {
	return color;
}

// Set the colour of the pixel, with double values
void Pixel::setColor(double _r, double _g, double _b) {
	color = ColorDBL(_r, _g, _b);
}

// Set the colour of the pixel, with ColorDBL
void Pixel::setColor(ColorDBL _color) {
	color = _color;
}