/*
    Written by Casper Larsson (casla195)
    for Linköping University TNCG15
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>


const int BAR_WIDTH = 40;

// Display a progress bar over the rendered/saved image
// Code from https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progressBar(float percent);

// Display the time in hours, minutes, seconds and milliseconds from seconds
void displayTime(int timeMilliseconds);

// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
// Code from https://cplusplus.com/forum/beginner/267364/
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y);