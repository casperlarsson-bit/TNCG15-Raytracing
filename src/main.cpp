#include <iostream>
#include "../include/Camera.h"
#include "../include/Scene.h"

int main() {
    Camera c{};
    Scene s{};

    s.createScene();
    c.renderImage(s);
    c.saveImage();

    system("cls");
    std::cout << "\nFinished!";
    return 0;
}