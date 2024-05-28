import EShortcutListener;

import eutilities;

#include <print>
#include <vector>

void callback()
{
	std::println("Shortcut triggered!");
}

int main()
{
	using eutilities::Key;
	// TESTS

	EShortcutListener::setTargetKeys({ Key::D, Key::K });
	EShortcutListener::setTargetKeys(Key::C);
	EShortcutListener::stopListening();

	std::vector<Key> keys{ Key::A, Key::F, Key::K, Key::O };
	EShortcutListener::setTargetKeys(keys);

	EShortcutListener::startListening(callback);
	EShortcutListener::stopListening();

	EShortcutListener::startListening(callback);
	eutilities::sleepFor(5000);
}