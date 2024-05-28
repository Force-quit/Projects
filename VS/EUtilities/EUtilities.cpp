module;

#include <iostream>
#include <thread>
#include <chrono>

module eutilities;

void eutilities::resetConsoleInput()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void eutilities::sleepFor(int iMsDuration)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(iMsDuration));
}