#include "pranker.h"
#include <Windows.h>
#include "../Utilities/utils.h"
#include <random>
#include <thread>

void resetInputBuffer()
{
	for (int key{ 0x01 }; key <= 0xFE; ++key)
		GetAsyncKeyState(key);
}

void waitForKeyRelease(const int key)
{
	while (GetAsyncKeyState(key))
		Sleep(5);
}

bool passwordIsTyped(const std::vector<int>& password, const size_t nextCharIndex)
{
	bool keyPress{};
	bool rightKeyPressed{};

	while (!keyPress)
	{
		for (int key{ 0x01 }; key <= 0xFE; ++key)
		{
			if (GetAsyncKeyState(key))
			{
				keyPress = true;
				waitForKeyRelease(key);
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

bool passwordIsTyped(const std::vector<int>& passwordKeys)
{
	return passwordIsTyped(passwordKeys, 0);
}

void prank_CAPSLOCK()
{
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

void startPranking(const bool& continuePranking)
{
	using prankFunctionType = void (*)();
	std::vector<prankFunctionType> prankFunctions{ prank_WINDOWS,
		prank_CAPSLOCK,
		//prank_BACKSPACE,
		//prank_CTRLV,
		//prank_RETURN,
		//prank_SPACE,
		//prank_ESCAPE
	};

	const int MAX_INDEX{ static_cast<int>(prankFunctions.size() - 1) };
	const int MIN_INTERVAL{ 15000 };
	const int MAX_INTERVAL{ 60000 };

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