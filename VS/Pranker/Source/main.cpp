import EUtilities;

#include "../Headers/RangedRandomGenerator.h"
#include "../Headers/PrankWorker.h"

#include <Windows.h>
#include <random>
#include <span>
#include <array>

static void resetInputBuffer()
{
	for (int key{ 0x01 }; key <= 0xFE; ++key)
		GetAsyncKeyState(key);
}

static bool passwordIsTyped(std::span<const int> password, const size_t nextCharIndex)
{
	bool wKeyPressed{};
	bool rightKeyPressed{};

	while (!wKeyPressed)
	{
		for (int key{ 0x01 }; key <= 0xFE; ++key)
		{
			if (GetAsyncKeyState(key))
			{
				wKeyPressed = true;
				EUtilities::waitForKeyRelease(key);
				rightKeyPressed = key == password[nextCharIndex];
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	if (!rightKeyPressed)
		return false;

	if (password.size() == nextCharIndex + 1)
		return true;

	return passwordIsTyped(password, nextCharIndex + 1);
}

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// emile le hacker
	static constexpr std::array<int, 15> passwordKeys
	{
		0x45, 0x4D, 0x49, 0x4C, 0x45,
		VK_SPACE,
		0x4C, 0x45,
		VK_SPACE,
		0x48, 0x41, 0x43, 0x4B, 0x45, 0x52
	};

	bool wContinuePranking{ true };

	PrankWorker prankWorker;

	resetInputBuffer();
	prankWorker.start();
	while (wContinuePranking)
		wContinuePranking = !passwordIsTyped(passwordKeys, 0);
	prankWorker.stop();

	MessageBoxA(NULL, "haha keyboard go bing bong", "Get pranked", MB_ICONINFORMATION | MB_SYSTEMMODAL);
	return EXIT_SUCCESS;
}