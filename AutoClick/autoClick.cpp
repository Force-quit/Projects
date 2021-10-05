#include <Windows.h>
#include <iostream>

void autoClick()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

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
				std::cout << "AutoClick : " << (clicking ? "Yes" : "No") << std::endl;
				keyDown = true;
			}
		}
		else
			keyDown = false;

		if (clicking)
		{
			SendInput(1, &mouseDown, sizeof(INPUT));
			Sleep(5);
			SendInput(1, &mouseUp, sizeof(INPUT));
		}

		if (GetAsyncKeyState('Q'))
			break;

		if (!clicking)
			Sleep(5);
	}
}

int main()
{
	SetConsoleTitleA("Clickster");
	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;
	autoClick();
	return 0;
}