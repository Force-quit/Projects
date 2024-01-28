import eutilities;

#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <optional>

static void addPressedKeys(std::vector<int>& pressedKeys)
{
	for (int i{ eutilities::MIN_VIRTUAL_KEY }; i <= eutilities::MAX_VIRTUAL_KEY; i++)
	{
		if (eutilities::isPressed(i))
		{
			pressedKeys.emplace_back(i);
		}
	}
}

static void printPressedKeys(const std::vector<int>& pressedKeys)
{
	std::cout << "Pressing : " << std::hex;
	for (auto i : pressedKeys)
	{
		std::optional<std::string> virtualKeyName(eutilities::nameOf(i));
		if (virtualKeyName)
		{
			std::cout << virtualKeyName.value() << " ";
		}
		// For testing
		else
		{
			std::cout << i << " (Unnamed) ";
		}
	}

	std::cout << '\n';
}

int main()
{
	std::vector<int> pressedKeys;
	while (!eutilities::isPressed(eutilities::ESCAPE))
	{
		addPressedKeys(pressedKeys);

		if (!pressedKeys.empty())
		{
			printPressedKeys(pressedKeys);
			pressedKeys.clear();
		}

		eutilities::sleepFor(1);
	}
}