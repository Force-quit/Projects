import InvertedMouseMover;
#include <iostream>

int main()
{
	InvertedMouseMover::startFor(1000);
	std::cin.get();
	auto b = InvertedMouseMover::isActive();
	InvertedMouseMover::stop();
}