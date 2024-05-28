import InvertedMouseMover;

#include <iostream>
#include <thread>

int main()
{
	InvertedMouseMover::startFor(1000);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << InvertedMouseMover::isActive() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}