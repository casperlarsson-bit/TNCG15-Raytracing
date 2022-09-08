#include <iostream>
#include "../include/Ray.h"
#include "../include/Triangle.h"
#include "../include/Rectangle.h"
#include "../include/Camera.h"

int main() {
    Camera c{};
    Ray r{};
    
    c.saveImage();

    std::cout << "Finished!";

    return 0;
}