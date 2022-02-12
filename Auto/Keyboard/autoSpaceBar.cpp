#include "../../Utilities/utils.h"
#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
	const std::string appName = "AutoSpaceBar";
	unsigned int timeBetween{};
	unsigned int keyHoldTime{};
	SetConsoleTitleA(appName.c_str());

	std::cout << appName<< std::endl;
	std::cout << "---------------------------------" << std::endl;

	do
	{
		emile::flushTampon();
		std::cout << "Key hold time : ";
		std::cin >> keyHoldTime;
	} while (std::cin.fail());

	do
	{
		emile::flushTampon();
		std::cout << "Time between keys : ";
		std::cin >> timeBetween;
	} while (std::cin.fail());

	if (timeBetween == 0)
		timeBetween = 1;

	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;


	bool pressing = false;
	bool keyDown = false;

	GetAsyncKeyState('X');
	GetAsyncKeyState('Q');

	while (!GetAsyncKeyState('Q'))
	{
		if (GetAsyncKeyState('X'))
		{
			if (!keyDown)
			{
				pressing = !pressing;
				std::cout << "Auto pressing : " << (pressing ? "Yes" : "No") << std::endl;
				keyDown = true;
			}
		}
		else
			keyDown = false;

		if (pressing)
		{
			emile::fullKeyPress(VK_SPACE);
			Sleep(timeBetween);
		}
		else
			Sleep(1);
	}
	return 0;
}