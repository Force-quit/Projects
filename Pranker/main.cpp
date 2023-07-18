#include <Windows.h>
#include "../Utilities/utils.h"
#include <thread>
#include "pranker.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bool continuePranking{ true };
	std::thread prankThread(startPranking, std::ref(continuePranking));

	const int STOP_KEY{ VK_NUMLOCK };

	GetAsyncKeyState(STOP_KEY);
	while (continuePranking)
	{
		Sleep(5);

		if (GetAsyncKeyState(STOP_KEY))
			continuePranking = false;
	}

	prankThread.join();
	MessageBoxA(NULL, "haha keyboard go bing bong", "Get pranked", MB_ICONINFORMATION);
	return 0;
}