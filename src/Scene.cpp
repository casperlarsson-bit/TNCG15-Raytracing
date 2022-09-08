#include "..\include\Scene.h"
#include "../include/glm/glm.hpp"

void Scene::createScene() {
	// Floor rectangle vertices
	rectangles[0].setVertices(glm::vec4(0, -6, -5, 1), glm::vec4(10, -6, -5, 1), glm::vec4(10, 6, -5, 1), glm::vec4(0, 6, -5, 1));

	// Floor triangles vertices
	triangles[0].setVertices(glm::vec4(10, -6, -5, 1), glm::vec4(13, 0, -5, 1), glm::vec4(10, 6, -5, 1));
	triangles[1].setVertices(glm::vec4(0, -6, -5, 1), glm::vec4(0, 6, -5, 1), glm::vec4(-3, 0, -5, 1));

	// Floor rectangle normal


	// Floor triangles normal

}