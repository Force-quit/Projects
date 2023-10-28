#include "../Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	unsigned int timeBetween{};
	unsigned int clickHoldTime{};
	SetConsoleTitleA("AutoClicker");

	std::cout << "AutoClicker" << std::endl;
	std::cout << "---------------------------------" << std::endl;

	do
	{
		emile::flushTampon();
		std::cout << "Click hold time : ";
		std::cin >> clickHoldTime;
	} while (std::cin.fail());

	do
	{
		emile::flushTampon();
		std::cout << "Time between clicks : ";
		std::cin >> timeBetween;
	} while (std::cin.fail());

	if (timeBetween == 0)
		timeBetween = 1;

	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;
	
	
	bool clicking = false;
	bool keyDown = false;

	GetAsyncKeyState('X');
	GetAsyncKeyState('Q');

	while (!GetAsyncKeyState('Q'))
	{
		if (GetAsyncKeyState('X'))
		{
			if (!keyDown)
			{
				clicking = !clicking;
				std::cout << "Auto clicking : " << (clicking ? "Yes" : "No") << std::endl;
				keyDown = true;
			}
		}
		else
			keyDown = false;

		if (clicking)
		{
			emile::leftClick(clickHoldTime);
			Sleep(timeBetween);
		}
		else
			Sleep(1);
	}
	return 0;
}