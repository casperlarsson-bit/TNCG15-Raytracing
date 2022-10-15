#include "../include/Camera.h"
#include <iostream>
#include <fstream>
#include <time.h>

// Default constructor sets resolution to 600x600
Camera::Camera() : image(SIZE, std::vector<Pixel>(SIZE)) {
	maxD = 0;
}

// Constructor which sets the resolution to res (square)
Camera::Camera(int _res) : image(_res, std::vector<Pixel>(_res)) {
	maxD = 0;
}

// Render the image by casting rays and changing the pixel value
void Camera::renderImage(Scene& scene) {
	// Loop through all pixels
	srand((int)time(NULL));
	std::cout << "Render image...\n";
	for (std::size_t i = 0; i < image.size(); ++i) {
		for (std::size_t j = 0; j < image.size(); ++j) {
			glm::vec3 pixelPosition = glm::vec3(0, 1 - 2 * (double)j / image.size(), 1 - 2 * (double)i / image.size());
			Ray pixelRay{eyePosition, pixelPosition - eyePosition};
			
			// Cast ray and let scene handle it. Set pixel colour to the 
			// colour of the Polygon it hits
			scene.castRay(pixelRay);
			image[i][j].setColor(pixelRay.getColor());

			// Update the max pixel value if new is found
			double newMax = glm::max(glm::max(pixelRay.getColor().red, pixelRay.getColor().blue), pixelRay.getColor().green);
			if (newMax > maxD) maxD = newMax;
		}

		// Display progress bar
		progressBar((double)i / image.size());
	}
}

// Save the image as file (.pmm)
void Camera::saveImage() const {
	// Save image. Code inspired by https://youtu.be/HGHbcRscFsg
	std::ofstream imageFile;
	imageFile.open("../Raytracing.pmm");

	if (!imageFile.is_open()) {
		std::cout << "Could not create file!\n";
		return;
	}

	imageFile << "P3\n" << image.size() << " " << image.size() << "\n255\n";

	// Access all pixels
	std::cout << "\nSaving image... \n";
	for (std::size_t i = 0; i < image.size(); ++i) {
		for (std::size_t j = 0; j < image.size(); ++j) {
			imageFile << (int)(image[i][j].getColor().red * 255 / maxD) << " " <<
				(int)(image[i][j].getColor().green * 255 / maxD) << " " <<	
				(int)(image[i][j].getColor().blue * 255 / maxD) << "\n";
		}
		
		// Display progress bar
		progressBar((double)i / image.size());
	}

	imageFile.close();
}