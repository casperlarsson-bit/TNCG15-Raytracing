#include "../include/Pixel.h"

// Default constructor
Pixel::Pixel() {

}

// Create pixel with colour
Pixel::Pixel(ColorDBL _color) {
	color = _color;
}

// Get colour of the pixel
ColorDBL Pixel::getColor() const {
	return color;
}

// Set the colour of the pixel, with float values
void Pixel::setColor(float _r, float _g, float _b) {
	color = ColorDBL(_r, _g, _b);
}

// Set the colour of the pixel, with ColorDBL
void Pixel::setColor(ColorDBL _color) {
	color = _color;
}