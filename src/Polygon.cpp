#include "../include/Polygon.h"

// Default constructor
Polygon::Polygon() {
	color = ColorDBL();
	normal = glm::vec3(1.0f, 0.0f, 0.0f);
	material = Material::LAMBERTIAN;
	rho = (color.red + color.green + color.blue) / 3.0f;
}

// Value constructor
Polygon::Polygon(ColorDBL _color, glm::vec3 _normal, Material _material) {
	if (_material == Material::MIRROR) {
		color = ColorDBL();
	}
	else {
		color = _color;
	}

	normal = _normal;
	material = _material;
	rho = (color.red + color.green + color.blue) / 3.0f;
}

// Compute the normal of the Polygon. Normal points into the room
glm::vec3 Polygon::getNormal() const {
	return glm::normalize(normal);
}

// Get the colour of the Polygon
ColorDBL Polygon::getColor() const {
	return color;
}

// Set the colour of the Polygon, and update rho
void Polygon::setColor(ColorDBL _color) {
	color = _color;
	rho = (color.red + color.green + color.blue) / 3.0f;
}

// Get what material the Polygon is made of
Material Polygon::getMaterial() const {
	return material;
}

// Sets the material of the Polygon
void Polygon::setMaterial(Material _material) {
	material = _material;

	if (_material == Material::MIRROR) {
		color = ColorDBL();
	}
}

// Get the Lambertian 
float Polygon::getRho() const {
	return rho;
}