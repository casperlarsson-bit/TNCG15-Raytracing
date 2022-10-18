#include <iostream>
#include "../include/Camera.h"
#include "../include/Scene.h"
#include <chrono> // Time rendering

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Camera c{};
    Scene s{};

    c.renderImage(s);
    c.saveImage();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    system("cls");
    std::cout << "\nFinished rendering in ";
    displayTime((int)duration.count());
    std::cout << "\n";
    return 0;
}