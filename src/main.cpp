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
    std::cout << "\nFinished rendering in " << (double)(duration.count()) / 1000 << " seconds!\n";
    return 0;
}