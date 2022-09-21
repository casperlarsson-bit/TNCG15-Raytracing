#include "../include/functions.h"

// Display a progress bar over the rendered/saved image
// Code from https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progressBar(double percent) {
	std::cout << "[";
	int pos = BAR_WIDTH * percent;
	for (int i = 0; i < BAR_WIDTH; ++i) {
		if (i <= pos) std::cout << "=";
		else std::cout << " ";
	}
	std::cout << "] " << int(percent * 100.0 + 0.5) << " %\r"; // +0.5 for round-off error
	std::cout.flush();
}