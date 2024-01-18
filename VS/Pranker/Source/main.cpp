#include "../Headers/PrankWorker.h"
#include "../Headers/PasswordWorker.h"
#include <Windows.h>

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	PrankWorker prankWorker;
	PasswordWorker passwordWorker;

	passwordWorker.start();
	prankWorker.start();

	passwordWorker.waitUntilPasswordIsTyped();
	prankWorker.stop();

	MessageBoxA(NULL, "Trg erxg abbo", "ROT13", MB_ICONINFORMATION | MB_SYSTEMMODAL);
} 