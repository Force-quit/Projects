#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "../Utilities/usefullshit.h"

int main()
{
	SetConsoleTitleA("Free skillz");
	const short nbInput = 4;
	INPUT keyBoardEvents[nbInput]{};
	INPUT mouseInput[2]{};

	short code{}; // 0=jump, 1=run
	std::cout << "1 : Jumping farm" << std::endl;
	std::cout << "2 : Running farm" << std::endl;
	std::cout << "3 : Hitting farm" << std::endl;

	std::cout << "Choice : ";

	do
	{
		code = _getch();
		flushTampons();
		switch (code)
		{
		case 49: code = 0; break;
		case 50: code = 1; break;
		case 51: code = 2; break;
		default: code = 69;
		}
	} while (code == 69);
	
	
	const short nbJumps = 13;
	const short runningTime = 18900;
	const short staminaRegenTime = 4400;
	const short timeToGetInGame = 1000;
	const short hittingTimes = 15;

	const short quitJumping = VK_LSHIFT;
	const short quitRunning = VK_SPACE;
	const short quitHitting = VK_LSHIFT;
	
	for (short i = 0; i < nbInput; ++i)
	{
		keyBoardEvents[i].type = INPUT_KEYBOARD;
		keyBoardEvents[i].ki.wScan = 0;
		keyBoardEvents[i].ki.time = 0;
		keyBoardEvents[i].ki.dwExtraInfo = 0;
	}	
	
	{
		HWND wind = FindWindowA(NULL, "Valheim");
		SetForegroundWindow(wind);
		SetActiveWindow(wind);
	}

	// If player has the pause menu
	/*keyBoardEvents[0].ki.dwFlags = 0;
	keyBoardEvents[0].ki.wVk = VK_ESCAPE;
	keyBoardEvents[1].ki.dwFlags = KEYEVENTF_KEYUP;
	keyBoardEvents[1].ki.dwFlags = VK_ESCAPE;
	SendInput(1, &keyBoardEvents[0], sizeof(INPUT));
	Sleep(700);
	SendInput(1, &keyBoardEvents[1], sizeof(INPUT));*/
	Sleep(300);
	switch (code)
	{
	case 0:
		// JUMPER, LSHIFT to quit
		keyBoardEvents[0].ki.wVk = VK_SPACE;
		keyBoardEvents[0].ki.dwFlags = 0; // KEYEVENTF_KEYDOWN
		keyBoardEvents[1].ki.wVk = VK_SPACE;
		keyBoardEvents[1].ki.dwFlags = KEYEVENTF_KEYUP;
		while (true)
		{
			for (int i = 0; i < nbJumps; i++)
			{
				SendInput(1, &keyBoardEvents[0], sizeof(INPUT));
				Sleep(50);
				SendInput(1, &keyBoardEvents[1], sizeof(INPUT));
				Sleep(150);
			}
			Sleep(staminaRegenTime);
			if (GetAsyncKeyState(quitJumping))
				return 0;
		}
		break;

	case 1: 
		// RUNNER, SPACE to quit
		keyBoardEvents[0].ki.wVk = 0x57; // W key
		keyBoardEvents[0].ki.dwFlags = 0; // KEYEVENTF_KEYDOWN
		keyBoardEvents[1].ki.wVk = 0x57;
		keyBoardEvents[1].ki.dwFlags = KEYEVENTF_KEYUP;

		keyBoardEvents[2].ki.wVk = VK_LSHIFT;
		keyBoardEvents[2].ki.dwFlags = 0;
		keyBoardEvents[3].ki.wVk = VK_LSHIFT;
		keyBoardEvents[3].ki.dwFlags = KEYEVENTF_KEYUP;
		while (true)
		{
			SendInput(1, &keyBoardEvents[0], sizeof(INPUT));
			SendInput(1, &keyBoardEvents[2], sizeof(INPUT));
			Sleep(runningTime);
			SendInput(1, &keyBoardEvents[1], sizeof(INPUT));
			SendInput(1, &keyBoardEvents[3], sizeof(INPUT));
			Sleep(staminaRegenTime);
			if (GetAsyncKeyState(quitRunning))
				return 0;
		}
		break;
	case 2:
		// Click lshift to quit
		mouseInput[0].type = INPUT_MOUSE;
		mouseInput[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

		mouseInput[1].type = INPUT_MOUSE;
		mouseInput[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		while (true)
		{
			for (int i = 0; i < hittingTimes; i++)
			{
				SendInput(1, &mouseInput[0], sizeof(INPUT));
				Sleep(200);
				SendInput(1, &mouseInput[1], sizeof(INPUT));
				Sleep(500);
			}
			Sleep(staminaRegenTime);
			if (GetAsyncKeyState(quitHitting))
				return 0;
		}

	}
}