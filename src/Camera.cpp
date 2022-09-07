#include "../include/Camera.h"

#include <iostream>

// Default constructor sets resolution to 600x600
Camera::Camera() : image(SIZE, std::vector<Pixel>(SIZE)) {

}

// Constructor which sets the resolution to res (square?)
Camera::Camera(int res) : image(res, std::vector<Pixel>(res)) {

}

// Render the image and save it as file (.jpg)
void Camera::renderImage() {
	// Loop through all pixels
	for (auto &row : image) {
		for (auto &pix : row) {
			// Cast ray into scene

		}
	}
}

// Save the image as file (.jpg?)
void Camera::saveImage() const {
	// Save image
	FILE* fp = fopen("Raytracing image.bmp", "wb");

	for (auto& row : image) {
		for (auto& pix : row) {
			// Get pixel
			unsigned char color[3];
			color[0] = (unsigned char)pix.getColor().red;
			color[1] = (unsigned char)pix.getColor().green;
			color[2] = (unsigned char)pix.getColor().blue;

			fwrite(color, 1, 3, fp);
		}
	}

	fclose(fp);
}