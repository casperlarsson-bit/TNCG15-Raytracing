#include "../include/Camera.h"
#include <iostream>
#include <fstream>

// Default constructor sets resolution to 600x600
Camera::Camera() : image(SIZE, std::vector<Pixel>(SIZE)) {

}

// Constructor which sets the resolution to res (square)
Camera::Camera(int res) : image(res, std::vector<Pixel>(res)) {

}

// Render the image by casting rays and changing the pixel value
void Camera::renderImage(Scene& _scene) {
	// Loop through all pixels
	std::cout << "Render image...\n";
	for (std::size_t i = 0; i < image.size(); ++i) {
		for (std::size_t j = 0; j < image.size(); ++j) {
			glm::vec4 pixelPosition = glm::vec4(0, 1 - 2 * (double)j / image.size(), 1 - 2 * (double)i / image.size(), 1);
			Ray pixelRay{eyePosition, glm::vec3(pixelPosition - eyePosition)};
			
			for (auto& rect : _scene.rectangles) {
				pixelRay.setEndVertex(rect.rayIntersection(pixelRay));
				std::cout << rect.v0[0] << " " << rect.v0[1] << " " << rect.v0[2] << "\n";
				std::cout << rect.v1[0] << " " << rect.v1[1] << " " << rect.v1[2] << "\n";
				std::cout << rect.v2[0] << " " << rect.v2[1] << " " << rect.v2[2] << "\n";
				std::cout << rect.v3[0] << " " << rect.v3[1] << " " << rect.v3[2] << "\n\n\n";
				if (pixelRay.getEndpoint()[0] == NULL) {
					continue;
				}
				image[i][j].setColor(pixelRay.getColor());

			}
			for (auto& tri : _scene.triangles) {
				pixelRay.setEndVertex(tri.rayIntersection(pixelRay));

				if (pixelRay.getEndpoint()[0] == NULL) {
					continue;
				}
				
				image[i][j].setColor(pixelRay.getColor());
			}
		}

		std::cout << (int)((double)i / image.size() * 100 + 0.5) << "% Complete\r";
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
	std::cout << "\nSave image...\n";
	for (std::size_t i = 0; i < image.size(); ++i) {
		for (std::size_t j = 0; j < image.size(); ++j) {
			// @TODO Scale for highest value in the scene
			imageFile << (int)(image[i][j].getColor().red * 255) << " " <<
				(int)(image[i][j].getColor().green * 255) << " " <<
				(int)(image[i][j].getColor().blue * 255) << "\n";
		}

		std::cout << (int)((double)i / image.size() * 100 + 0.5) << "% Complete\r";
	}

	imageFile.close();
}