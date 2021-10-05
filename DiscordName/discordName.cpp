#include <iostream>
#include <Windows.h>
#include <vector>
#include "../Utilities/usefullshit.h"
#include <string>

const char caracters[76] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
										 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
										 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
										 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
										 '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
										 '#', '\\', '|', '!', '@', '/', '\\', '$', '%', '?', '&', '*', '(', ')' };
char newName[32];

void passwordGenerator()
{
	for (USHORT i = 0; i < sizeof(newName); ++i)
		newName[i] = 0;

	for (UINT16 i = 0; i < 32; ++i) // rand() % 32 + 5
		newName[i] = caracters[rand() % sizeof(caracters)];
}

POINT getCursorPos()
{
	POINT p{};
	while (true)
	{
		if (GetAsyncKeyState(VK_CAPITAL))
		{
			while (true)
				if (!GetAsyncKeyState(VK_CAPITAL))
					break;
			GetCursorPos(&p);
			std::cout << "X : " << p.x << " Y : " << p.y << std::endl;
			return p;
		}
	}
}

void keyboardPress(INPUT& input, WORD key)
{
	input.ki.wVk = key;
	input.ki.dwFlags = 0;
}

void keyboardRelease(INPUT& input, WORD key)
{
	
}

int main()
{
	srand(time(0));
	std::vector<POINT> points = std::vector<POINT>();
	std::cout << "Get four cursor positions and your mouse will replay your positions" << "\n\n";
	bool exit = false;
	while (!exit)
	{
		std::cout << "Press caps lock to get cursor position" << std::endl;

		for (short i = 0; i < 2; i++)
			points.push_back(getCursorPos());

		std::cout << std::endl << "Press 'Q' to quit or 'R' to restart" << std::endl;
		while (true)
		{
			if (GetAsyncKeyState(VK_LSHIFT))
			{
				exit = true;
				break;
			}
			else if (GetAsyncKeyState('R'))
				break;
		}
	}

	INPUT click[2]{};
	click[0].type = INPUT_MOUSE;
	click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	click[1].type = INPUT_MOUSE;
	click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	INPUT keyBoardEvents{};
	keyBoardEvents.type = INPUT_KEYBOARD;
	keyBoardEvents.ki.wScan = 0;
	keyBoardEvents.ki.time = 0;
	keyBoardEvents.ki.dwExtraInfo = 0;
	for (int a = 0; a < 5; ++a)
	{
		SetCursorPos(points.at(0).x, points.at(0).y);
		SendInput(ARRAYSIZE(click), click, sizeof(INPUT));
		Sleep(400);
		SetCursorPos(points.at(1).x, points.at(1).y);
		SendInput(ARRAYSIZE(click), click, sizeof(INPUT));
		Sleep(400);

		
		keyboardPress(keyBoardEvents, VK_CONTROL);
		SendInput(1, &keyBoardEvents, sizeof(INPUT));

	
		keyBoardEvents.ki.wVk = 'A';
		keyBoardEvents.ki.dwFlags = 0; 
		SendInput(1, &keyBoardEvents, sizeof(INPUT));

	
		keyBoardEvents.ki.wVk = 'A';
		keyBoardEvents.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &keyBoardEvents, sizeof(INPUT));

	
		keyBoardEvents.ki.wVk = VK_CONTROL;
		keyBoardEvents.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &keyBoardEvents, sizeof(INPUT));

		passwordGenerator();
		Sleep(400);

		for (USHORT i = 0; i < sizeof(newName); i++)
		{
			keyBoardEvents.ki.wVk = VkKeyScanA(newName[i]);
			keyBoardEvents.ki.dwFlags = 0;
			SendInput(1, &keyBoardEvents, sizeof(INPUT));
			keyBoardEvents.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &keyBoardEvents, sizeof(INPUT));
			Sleep(5);
		}

		Sleep(400);
		keyBoardEvents.ki.wVk = VK_RETURN;
		keyBoardEvents.ki.dwFlags = 0;
		SendInput(1, &keyBoardEvents, sizeof(INPUT));
		keyBoardEvents.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &keyBoardEvents, sizeof(INPUT));
		Sleep(700);
	}
}