#pragma once

#include <iostream>
#include <vector>
#include "Pixel.h"
#include "glm/glm.hpp"

const int SIZE = 600; // Default image resolution (square)

class Camera {
public:
	// Default constructor sets resolution to 600x600
	Camera();

	// Constructor which sets the resolution to res (square?)
	Camera(int res);

	// Render the image 
	void renderImage();

	// Save the image as file (.jpg?)
	void saveImage() const;
	
private:
	std::vector<std::vector<Pixel>> image;
	glm::vec3 eyePosition = glm::vec3(-1, 0, 0);
};