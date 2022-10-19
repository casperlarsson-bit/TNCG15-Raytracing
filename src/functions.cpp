#include "../include/functions.h"

// Display a progress bar over the rendered/saved image
// Code from https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progressBar(float percent) {
	std::cout << "[";
	int pos = (int)(BAR_WIDTH * percent);
	for (int i = 0; i < BAR_WIDTH; ++i) {
		if (i <= pos) std::cout << "=";
		else std::cout << " ";
	}
	std::cout << "] " << int(percent * 100.0f + 0.5f) << " %\r"; // +0.5 for round-off error
	std::cout.flush();
}

// Display the time in hours, minutes, seconds and milliseconds from seconds
void displayTime(int timeMilliseconds) {
	int seconds = timeMilliseconds / 1000;
	int minutes = seconds / 60;
	int hours = minutes / 60;

	int milliseconds = timeMilliseconds % 1000;
	seconds %= 60;
	minutes %= 60;

	std::cout << std::setfill('0');
	if (hours > 0) std::cout << std::setw(2) << hours << ":";
	if (minutes > 0) std::cout << std::setw(2) << minutes << ":";
	if (seconds > 0) std::cout << std::setw(2) << seconds << ".";
	std::cout << std::setw(3) << milliseconds;
}