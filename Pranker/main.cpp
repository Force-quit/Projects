#include <Windows.h>
#include "../Utilities/utils.h"
#include <iostream>
#include <random>

void prank_CAPSLOCK()
{
	if (GetKeyState(VK_CAPITAL) == 0)
		emile::fullKeyPress(VK_CAPITAL);
}

void prank_WINDOWS()
{
	emile::fullKeyPress(VK_LWIN);
}

void prank_SPACE()
{
	emile::fullKeyPress(VK_SPACE);
}

void prank_RETURN()
{
	emile::fullKeyPress(VK_RETURN);
}

void prank_BACKSPACE()
{
	emile::fullKeyPress(VK_BACK);
}

void prank_CTRLV()
{
	emile::ctrlV();
}

void prank_ESCAPE()
{
	emile::fullKeyPress(VK_ESCAPE);
}

int main()
{	
	FreeConsole();
	using prank_function_type = void (*)();

	std::vector<prank_function_type> prankFunctions;
	prankFunctions.push_back(prank_WINDOWS);
	prankFunctions.push_back(prank_CAPSLOCK);
	prankFunctions.push_back(prank_BACKSPACE);
	prankFunctions.push_back(prank_CTRLV);
	prankFunctions.push_back(prank_RETURN);
	prankFunctions.push_back(prank_SPACE);
	prankFunctions.push_back(prank_ESCAPE);
	
	const int MAX_INDEX{ static_cast<int>(prankFunctions.size() - 1) };
	const int MIN_INTERVAL{ 30000 };
	const int MAX_INTERVAL{ 120000 };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> indexDistr(0, MAX_INDEX);
	std::uniform_int_distribution<> intervalDistr(MIN_INTERVAL, MAX_INTERVAL);

	GetAsyncKeyState(VK_RCONTROL);
	std::clock_t start{};
	std::clock_t nextEvent{};
	bool userQuit{};

	while (!userQuit)
	{
		start = std::clock();
		nextEvent = intervalDistr(gen);

		while (std::clock() - start < nextEvent)
		{
			Sleep(5);

			if (GetAsyncKeyState(VK_RCONTROL))
			{
				userQuit = true;
				break;
			}
		}

		if (!userQuit)
			prankFunctions[indexDistr(gen)]();
	}

	MessageBoxA(NULL, "haha keyboard go bing bong", "Get pranked", MB_ICONINFORMATION);

	return 0;
}