#pragma once
#include <iostream>

const int BAR_WIDTH = 40;

// Display a progress bar over the rendered/saved image
// Code from https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progressBar(double percent);