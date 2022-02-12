#include "../Projects/Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	unsigned short timeBetween{};
	unsigned short clickHoldTime{};
	SetConsoleTitleA("AutoRightClicker");

	std::cout << "AutoRightClicker" << std::endl;
	std::cout << "---------------------------------" << std::endl;
	do
	{
		e_flushTampon();
		std::cout << "Time between clicks : ";
		std::cin >> timeBetween;
	} while (std::cin.fail() || timeBetween == 0);

	do
	{
		e_flushTampon();
		std::cout << "Click time : ";
		std::cin >> clickHoldTime;
	} while (std::cin.fail() || clickHoldTime == 0);

	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;


	bool clicking = false;
	bool keyDown = false;

	GetAsyncKeyState('X');
	GetAsyncKeyState('Q');
	while (true)
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
			e_rightClick(clickHoldTime);

		Sleep(timeBetween);

		if (GetAsyncKeyState('Q'))
			break;

	}
	return 0;
}