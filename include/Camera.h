/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once

#include <iostream>
#include <vector>
#include "Pixel.h"
#include "Ray.h"
#include "Scene.h"
#include "glm/glm.hpp"
#include "functions.h"

const int SIZE = 600; // Default image resolution (square)
const int NUMBER_OF_SUBPIXELS = 6; // numbers of rays to cast through each pixel (squared)

class Camera {
public:
	// Default constructor sets resolution to 600x600
	Camera();

	// Constructor which sets the resolution to res (square?)
	Camera(int res);

	// Render the image 
	void renderImage(Scene& _scene);

	// Save the image as file
	void saveImage() const;
	
private:
	std::vector<std::vector<Pixel>> image;
	glm::vec3 eyePosition = glm::vec3(-0.5f, 0.0f, 0.0f);
	float maxD; // Maximum value in the image, to divide all pixels when saving image
};