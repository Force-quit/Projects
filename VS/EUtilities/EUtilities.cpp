module;

#include <iostream>

module eutilities;

void eutilities::resetConsoleInput()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}