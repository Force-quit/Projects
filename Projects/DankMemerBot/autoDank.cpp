#include "../Console(v1.9)/console(v1.9).h"
#include "../Utilities/usefullshit.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>

void enterCommand(std::vector<UINT16>& keys)
{
	INPUT enterKey{};
	enterKey.type = INPUT_KEYBOARD;
	enterKey.ki.wVk = VK_RETURN;
	humanType(keys);
	pressKey(enterKey);
	Sleep(600);
}

int main()
{
	std::cout << "Press insert to run commands. Press for 3 seconds and close program.";
	std::clock_t start{};
	double duration{};
	bool keyDown = false;
	GetAsyncKeyState(VK_INSERT);
	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT))
		{
			if (!keyDown)
			{
				keyDown = true;
				start = std::clock();
			}
			else if ((std::clock() - start) / (double)CLOCKS_PER_SEC >= 3)
				return 0;
		}
		else
		{
			if (keyDown)
			{
				keyDown = false;
				HWND discordWindow = FindWindowA(NULL, "dank-memer - Discord");
				if (discordWindow)
				{
					SetForegroundWindow(discordWindow);


					std::vector<UINT16> keys{};

					while (true)		
					{
						keys = { 0x50, 0x4C, 0x53, 0x20, 0x42, 0x45, 0x47 }; // beg
						enterCommand(keys);
						keys.clear();
						Sleep(30000);
					}


					keys = { 0x50, 0x4C, 0x53, 0x20, 0x48, 0x55, 0x4E, 0x54 }; // hunt
					enterCommand(keys);
					keys.clear();

					keys = { 0x50, 0x4C, 0x53, 0x20, 0x44, 0x49, 0x47 }; // dig
					enterCommand(keys);
					keys.clear();

					keys = { 0x50, 0x4C, 0x53, 0x20, 0x46, 0x49, 0x53, 0x48 }; // fish
					enterCommand(keys);
					keys.clear();

					keys = { 0x50, 0x4C, 0x53, 0x20, 0x53, 0x45, 0x41, 0x52, 0x43, 0x48 }; // search
					enterCommand(keys);
					keys.clear();

					//keys = { 0x50, 0x4C, 0x53, 0x20, 0x50, 0x4D }; // pm
					//enterCommand(keys);
					//keys.clear();

					/*Sleep(2500);
					if (!GetAsyncKeyState('A'))
					{
						INPUT alt{};
						INPUT tab{};
						alt.type = tab.type = INPUT_KEYBOARD;
						alt.ki.wVk = VK_MENU;
						tab.ki.wVk = VK_TAB;
						SendInput(1, &alt, sizeof(INPUT));
						Sleep(40);
						SendInput(1, &tab, sizeof(INPUT));
						Sleep(40);
						alt.ki.dwFlags = KEYEVENTF_KEYUP;
						tab.ki.dwFlags = KEYEVENTF_KEYUP;
						SendInput(1, &alt, sizeof(INPUT));
						Sleep(40);
						SendInput(1, &tab, sizeof(INPUT));
					}*/
				}
			}
		}
	}
}