import EShortcutListener;

import eutilities;

#include <print>
#include <vector>
#include <thread>

using eutilities::Key;

void callback()
{
	std::println("Shortcut triggered from thread {}", std::this_thread::get_id());
}

void tests()
{
	EShortcutListener listener;

	listener.setTargetKeys({ Key::D, Key::K });
	listener.setTargetKeys(Key::C);
	listener.stopListening();

	std::vector keys{ Key::A, Key::D };
	listener.setTargetKeys(keys);

	listener.startListening(callback);
	listener.stopListening();
}

int main()
{
	EShortcutListener listener1;
	listener1.setTargetKeys(Key::A);

	EShortcutListener listener2;
	listener2.setTargetKeys(Key::S);

	listener1.startListening(callback);
	listener2.startListening(callback);
	eutilities::sleepFor(5000);
}