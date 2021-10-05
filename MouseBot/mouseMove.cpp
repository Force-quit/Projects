#include <iostream>
#include <Windows.h>


int main()
{
	INPUT f5{};
	f5.type = INPUT_KEYBOARD;
	f5.ki.wVk = VK_F5;
	
	Sleep(3000);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		SendInput(1, &f5, sizeof(INPUT));
	}
}