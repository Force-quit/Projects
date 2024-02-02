import eutilities;
import EShortcutListener;
#include <vector>
#include <iostream>
#include <functional>

int main()
{
	std::vector<eutilities::Key> a =
	{
		eutilities::Key::CAPSLOCK,
	};

	EShortcutListener::setTargetKeys(a);
	EShortcutListener::startListening([]{eutilities::fullKeyPress(eutilities::WINDOWS); });
	std::cin.get();
}