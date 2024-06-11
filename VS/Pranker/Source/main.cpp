import Pranker;

#include <Windows.h>

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	PasswordWorker::start();
	PrankWorker::start();

	PasswordWorker::waitUntilPasswordIsTyped();
	PrankWorker::stop();

	MessageBoxA(nullptr, "Trg erxg abbo", "ROT13", MB_ICONINFORMATION | MB_SYSTEMMODAL);
} 