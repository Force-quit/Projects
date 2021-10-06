#include "../Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	SetConsoleTitleA("AutoClicker");
	consoleBundle();

	std::cout << "AutoClicker" << std::endl;
	std::cout << "---------------------------------" << std::endl;
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
			e_click(1);
		else
			Sleep(1);

		if (GetAsyncKeyState('Q'))
			break;

	}
	return 0;
}