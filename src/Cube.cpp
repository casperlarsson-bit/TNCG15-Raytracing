/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#include "../include/Cube.h"

// Default construcot
Cube::Cube() {
    glm::vec3 _midVertex = glm::vec3(5.0f, 0.0f, 1.0f);
    float size = 1.0;

    // Top
    vertexTable[0] = glm::vec3(size + _midVertex.x, size + _midVertex.y, size + _midVertex.z);
    vertexTable[1] = glm::vec3(-size + _midVertex.x, size + _midVertex.y, size + _midVertex.z);
    vertexTable[2] = glm::vec3(-size + _midVertex.x, -size + _midVertex.y, size + _midVertex.z);
    vertexTable[3] = glm::vec3(size + _midVertex.x, -size + _midVertex.y, size + _midVertex.z);

    // Bottom
    vertexTable[4] = glm::vec3(size + _midVertex.x, size + _midVertex.y, -size + _midVertex.z);
    vertexTable[5] = glm::vec3(-size + _midVertex.x, size + _midVertex.y, -size + _midVertex.z);
    vertexTable[6] = glm::vec3(-size + _midVertex.x, -size + _midVertex.y, -size + _midVertex.z);
    vertexTable[7] = glm::vec3(size + _midVertex.x, -size + _midVertex.y, -size + _midVertex.z);

    // https://www.geogebra.org/3d/pvpxbrjx
    rectangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2], vertexTable[3]); // Top
    rectangleTable[1].setVertices(vertexTable[4], vertexTable[0], vertexTable[3], vertexTable[7]);
    rectangleTable[2].setVertices(vertexTable[5], vertexTable[1], vertexTable[0], vertexTable[4]);
    rectangleTable[3].setVertices(vertexTable[6], vertexTable[2], vertexTable[1], vertexTable[5]);
    rectangleTable[4].setVertices(vertexTable[7], vertexTable[3], vertexTable[2], vertexTable[6]);
    rectangleTable[5].setVertices(vertexTable[5], vertexTable[4], vertexTable[7], vertexTable[6]); // Bottom

    material = Material::LAMBERTIAN;
    color = ColorDBL();
    for (auto& rectangle : rectangleTable) {
        rectangle.setColor(ColorDBL());
        rectangle.calculateNormal();
    }
}

// Value constructor
Cube::Cube(glm::vec3 _midVertex, float size, ColorDBL _color, Material _material) {
    // Top
    vertexTable[0] = glm::vec3(size + _midVertex.x, size + _midVertex.y, size + _midVertex.z);
    vertexTable[1] = glm::vec3(-size + _midVertex.x, size + _midVertex.y, size + _midVertex.z);
    vertexTable[2] = glm::vec3(-size + _midVertex.x, -size + _midVertex.y, size + _midVertex.z);
    vertexTable[3] = glm::vec3(size + _midVertex.x, -size + _midVertex.y, size + _midVertex.z);

    // Bottom
    vertexTable[4] = glm::vec3(size + _midVertex.x, size + _midVertex.y, -size + _midVertex.z);
    vertexTable[5] = glm::vec3(-size + _midVertex.x, size + _midVertex.y, -size + _midVertex.z);
    vertexTable[6] = glm::vec3(-size + _midVertex.x, -size + _midVertex.y, -size + _midVertex.z);
    vertexTable[7] = glm::vec3(size + _midVertex.x, -size + _midVertex.y, -size + _midVertex.z);

    rectangleTable[0].setVertices(vertexTable[0], vertexTable[1], vertexTable[2], vertexTable[3]); // Top
    rectangleTable[1].setVertices(vertexTable[4], vertexTable[0], vertexTable[3], vertexTable[7]);
    rectangleTable[2].setVertices(vertexTable[5], vertexTable[1], vertexTable[0], vertexTable[4]);
    rectangleTable[3].setVertices(vertexTable[6], vertexTable[2], vertexTable[1], vertexTable[5]);
    rectangleTable[4].setVertices(vertexTable[7], vertexTable[3], vertexTable[2], vertexTable[6]);
    rectangleTable[5].setVertices(vertexTable[5], vertexTable[4], vertexTable[7], vertexTable[6]); // Bottom

    material = _material;
    color = _color;

    for (auto& rectangle : rectangleTable) {
        rectangle.setColor(_color);
        rectangle.setMaterial(_material);
        rectangle.calculateNormal();
    }

    rectangleTable[0].setTexture("../textures/grass.png");
    rectangleTable[1].setTexture("../textures/minecraft.png");
    rectangleTable[2].setTexture("../textures/minecraft.png");
    rectangleTable[3].setTexture("../textures/minecraft.png");
    rectangleTable[4].setTexture("../textures/minecraft.png");
    rectangleTable[5].setTexture("../textures/minecraft.png");
}

// Get what material the Cube is made of
Material Cube::getMaterial() const {
    return material;
}

// Set the material of the Cube
void Cube::setMaterial(Material _material) {
    material = _material;
    for (auto& rectangle : rectangleTable) {
        rectangle.setMaterial(_material);
    }
}

// Get the colour of the Cube
ColorDBL Cube::getColor() const {
    return color;
}

// Set the colour of the Cube
void Cube::setColor(ColorDBL _color) {
    color = _color;
    for (auto& rectangle : rectangleTable) {
        rectangle.setColor(_color);
    }
}

// Calculate the intersection of a ray and the surface
void Cube::rayIntersection(Ray& ray, float& minDistance) const {
    for (auto& rectangle : rectangleTable) {
        if (glm::dot(rectangle.getNormal(), ray.getDirection()) > COMPARE_ELLIPSE) continue;
        if (rectangle.rayIntersection(ray, minDistance)) break;
    }
}