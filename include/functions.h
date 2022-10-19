#pragma once
#include <iostream>
#include <iomanip>

const int BAR_WIDTH = 40;

// Display a progress bar over the rendered/saved image
// Code from https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progressBar(float percent);

// Display the time in hours, minutes, seconds and milliseconds from seconds
void displayTime(int timeMilliseconds);