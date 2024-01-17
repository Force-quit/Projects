import EUtilities;

#include <Windows.h>
#include <random>
#include <span>
#include <thread>
#include <array>

static void resetInputBuffer()
{
	for (int key{ 0x01 }; key <= 0xFE; ++key)
		GetAsyncKeyState(key);
}

static bool passwordIsTyped(std::span<int> password, const size_t nextCharIndex)
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

		Sleep(5);
	}

	if (!rightKeyPressed)
		return false;

	if (password.size() == nextCharIndex + 1)
		return true;

	return passwordIsTyped(password, nextCharIndex + 1);
}

static void startPranking(const bool& continuePranking)
{
	using prankFunctionType = void (*)();
	std::vector<prankFunctionType> prankFunctions{
		[]() {EUtilities::fullKeyPress(VK_LWIN); },
		[]() {EUtilities::fullKeyPress(VK_CAPITAL); },

		/* Dangerous functions
		[]() {EUtilities::fullKeyPress(VK_SPACE); },
		[]() {EUtilities::fullKeyPress(VK_RETURN); },
		[]() {EUtilities::fullKeyPress(VK_BACK); },
		[]() {EUtilities::ctrlV(); },
		[]() {EUtilities::fullKeyPress(VK_ESCAPE); }
		*/
	};

	const int MAX_INDEX{ static_cast<int>(prankFunctions.size() - 1) };
	static constexpr int MIN_INTERVAL{ 15000 };
	static constexpr int MAX_INTERVAL{ 30000 };

	std::random_device randomDevice;
	std::mt19937 randomGenerator(randomDevice());
	std::uniform_int_distribution<> indexDistribution(0, MAX_INDEX);
	std::uniform_int_distribution<> intervalDistribution(MIN_INTERVAL, MAX_INTERVAL);

	std::clock_t lastPrankTime{};
	std::clock_t randomInterval{};

	while (continuePranking)
	{
		lastPrankTime = std::clock();
		randomInterval = intervalDistribution(randomGenerator);

		while (std::clock() - lastPrankTime < randomInterval && continuePranking)
			Sleep(5);

		if (continuePranking)
			prankFunctions[indexDistribution(randomGenerator)]();
	}
}

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	bool wContinuePranking{ true };
	std::thread prankThread(startPranking, std::cref(wContinuePranking));

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	// emile le hacker
	std::array<int, 15> passwordKeys{
		0x45, 0x4D, 0x49, 0x4C, 0x45,
		VK_SPACE,
		0x4C, 0x45,
		VK_SPACE,
		0x48, 0x41, 0x43, 0x4B, 0x45, 0x52
	};

	resetInputBuffer();

	while (wContinuePranking)
		wContinuePranking = !passwordIsTyped(passwordKeys, 0);

	prankThread.join();
	MessageBoxA(NULL, "haha keyboard go bing bong", "Get pranked", MB_ICONINFORMATION | MB_SYSTEMMODAL);
	return EXIT_SUCCESS;
}