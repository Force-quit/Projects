#include <iostream>
#include <Windows.h>

int main()
{
	Sleep(3000);
	HWND minecraftWindow{ GetForegroundWindow() };
	std::cout << "Got it\n";
	Sleep(3000);
	std::cout << "Go now\n";

	if (!PostMessage(minecraftWindow, WM_KEYDOWN, 0x41, NULL))
		std::cout << GetLastError() << std::endl;

	Sleep(200);

	if (!PostMessage(minecraftWindow, WM_KEYUP, 0x41, NULL))
		std::cout << GetLastError() << std::endl;

	Sleep(5000);
	return EXIT_SUCCESS;
}