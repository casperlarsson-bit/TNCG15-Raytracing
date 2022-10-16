#include "../include/Camera.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <random> // Default random engine

std::default_random_engine seeds;
std::uniform_real_distribution<float> distributions(-0.5f, 0.5f);

// Default constructor sets resolution to 600x600
Camera::Camera() : image(SIZE, std::vector<Pixel>(SIZE)) {
	maxD = 0.0f;
}

// Constructor which sets the resolution to res (square)
Camera::Camera(int _res) : image(_res, std::vector<Pixel>(_res)) {
	maxD = 0.0f;
}

// Render the image by casting rays and changing the pixel value
void Camera::renderImage(Scene& scene) {
	// Loop through all pixels
	srand((int)time(NULL)); // Useless?

	const float pixelLength = (1.0f / (float)image.size());
	std::cout << "Render image...\n";
	for (std::size_t i = 0; i < image.size(); ++i) {
		for (std::size_t j = 0; j < image.size(); ++j) {
			//glm::vec3 pixelPosition = glm::vec3(0.0f, 1.0f - 2.0f * (float)j / image.size(), 1.0f - 2.0f * (float)i / image.size());
			glm::vec3 pixelPosition = glm::vec3(0.0f, ((float)image.size() / 2.0f - (float)j + 0.5f) * pixelLength, ((float)image.size() / 2.0f - (float)i + 0.5f) * pixelLength); // Centre position of the pixel
			ColorDBL sampledPixelColor = ColorDBL();

			
			for (int n = 0; n < NUMBER_OF_SUBPIXELS; ++n) {
				for (int m = 0; m < NUMBER_OF_SUBPIXELS; ++m) {
					glm::vec3 subPixel = pixelPosition + glm::vec3(0, ((float)NUMBER_OF_SUBPIXELS / 2.0f - n + distributions(seeds)) * pixelLength / NUMBER_OF_SUBPIXELS, ((float)NUMBER_OF_SUBPIXELS / 2.0f - m + distributions(seeds)) * pixelLength / NUMBER_OF_SUBPIXELS);


					Ray pixelRay{eyePosition, subPixel - eyePosition};
			
					// Cast ray and let scene handle it. Set pixel colour to the 
					// colour of the Polygon it hits
					scene.castRay(pixelRay);
					sampledPixelColor += pixelRay.getColor();

				}
			}
			
			
			ColorDBL pixelColor = sampledPixelColor * (1.0f / ((float)NUMBER_OF_SUBPIXELS * (float)NUMBER_OF_SUBPIXELS));
			
			image[i][j].setColor(pixelColor);
			
			// Update the max pixel value if new is found
			float newMax = glm::max(glm::max(pixelColor.red, pixelColor.blue), pixelColor.green);
			if (newMax > maxD) maxD = newMax;
		}

		// Display progress bar
		progressBar((float)i / image.size());
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
		progressBar((float)i / image.size());
	}

	imageFile.close();
}