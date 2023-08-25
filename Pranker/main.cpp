#include <Windows.h>
#include <thread>
#include "pranker.h"

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	bool passwordWasTyped{};
	std::thread prankThread(startPranking, std::ref(passwordWasTyped));

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	const std::vector<int> passwordKeys{ 
		0x45, 0x4D, 0x49, 0x4C, 0x45,
		VK_SPACE,
		0x4C, 0x45,
		VK_SPACE,
		0x48, 0x41, 0x43, 0x4B, 0x45, 0x52
	};

	resetInputBuffer();
	
	while (!passwordWasTyped)
		passwordWasTyped = passwordIsTyped(passwordKeys);

	prankThread.join();
	MessageBoxA(NULL, "haha keyboard go bing bong", "Get pranked", MB_ICONINFORMATION | MB_SYSTEMMODAL);
	return 0;
}