#include <iostream>
#include <Windows.h>



int main()
{
	std::cout << "Press escape to quit";
	INPUT f5Press{};
	f5Press.type = INPUT_KEYBOARD;
	f5Press.ki.wVk = VK_F5;

	INPUT f5Release{};
	f5Release.type = INPUT_KEYBOARD;
	f5Release.ki.wVk = VK_F5;
	f5Release.ki.dwFlags = KEYEVENTF_KEYUP;

	Sleep(3000);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		SendInput(1, &f5Press, sizeof(INPUT));
		Sleep(100);
		SendInput(1, &f5Release, sizeof(INPUT));
	}
}