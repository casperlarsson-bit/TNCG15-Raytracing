#include <iostream>
// #include "../include/Ray.h"
// #include "../include/Triangle.h"
// #include "../include/Rectangle.h"
#include "../include/Camera.h"
#include "../include/Scene.h"

int main() {
    Camera c{800};
    Scene s{};

    s.createScene();
    c.renderImage(s);
    c.saveImage();

    std::cout << "\nFinished!";

    return 0;
}