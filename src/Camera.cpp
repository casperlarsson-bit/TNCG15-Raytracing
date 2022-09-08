#include "../include/Camera.h"
#include <iostream>
#include <fstream>

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
			// @TODO Cast ray into scene

		}
	}
}

// Save the image as file (.jpg?)
void Camera::saveImage() const {
	// Save image. Code inspired by https://youtu.be/HGHbcRscFsg
	std::ofstream imageFile;
	imageFile.open("Raytracing.pmm");

	if (!imageFile.is_open()) {
		std::cout << "Could not create file!\n";
		return;
	}

	imageFile << "P3\n" << image.size() << " " << image.size() << "\n255\n";

	// Access all pixels
	for (auto& row : image) {
		for (auto& pix : row) {
			// @TODO Scale for highest value in the scene
			imageFile << pix.getColor().red * 255 << " " <<
				pix.getColor().green * 255 << " " <<
				pix.getColor().blue * 255 << "\n";
		}
	}

	imageFile.close();
}