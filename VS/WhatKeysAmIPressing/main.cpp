import eutilities;

#include <vector>
#include <string>
#include <print>
#include <span>

void addPressedKeys(std::vector<eutilities::Key>& pressedKeys)
{
	for (auto key : eutilities::keys)
	{
		if (eutilities::isPressed(key))
		{
			pressedKeys.push_back(key);
		}
	}
}

void printPressedKeys(std::span<eutilities::Key> pressedKeys)
{
	std::print("Pressing : ");

	for (auto i : pressedKeys)
	{
		std::print("{} ", eutilities::nameOf(i));
	}

	std::println("");
}

int main()
{
	std::vector<eutilities::Key> pressedKeys;
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