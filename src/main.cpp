#include <iostream>
#include "../include/Ray.h"
#include "../include/Camera.h"

int main() {
    Camera c{};
    c.saveImage();

    std::cout << "Hello world";
    return 0;
}