module;

#include <iostream>
#include <thread>

module eutilities;

void eutilities::resetConsoleInput()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void eutilities::sleepFor(int msDuration)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(msDuration));
}