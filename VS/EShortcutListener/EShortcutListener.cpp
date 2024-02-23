module;

#include <functional>
#include <vector>
#include <initializer_list>

module EShortcutListener;
import eutilities;

void EShortcutListener::startListening(std::function<void()> callbackFunc)
{
	callbackFunction = callbackFunc;
	stopListening();
	listenLoop = std::jthread(&EShortcutListener::mainLoop);
}

void EShortcutListener::stopListening()
{
	if (listenLoop.joinable())
	{
		listenLoop.request_stop();
		listenLoop.join();
	}
}

void EShortcutListener::mainLoop(std::stop_token iStopToken)
{
	uint8_t pressedKeys{};
	bool canTrigger{ true };

	while (!iStopToken.stop_requested())
	{
		for (auto& i : shortcutKeys)
		{
			if (eutilities::isPressed(i))
			{
				++pressedKeys;
				if (pressedKeys == shortcutKeys.size() && canTrigger)
				{
					callbackFunction();
					canTrigger = false;
				}
			}
			else
			{
				pressedKeys = 0;
				canTrigger = true;
			}
		}

		eutilities::sleepFor(5);
	}
}

std::vector<eutilities::Key> EShortcutListener::targetKeys()
{
	return shortcutKeys;
}

bool EShortcutListener::isListening()
{
	return listenLoop.joinable();
}

void EShortcutListener::setTargetKeys(std::initializer_list<eutilities::Key> keys)
{
	shortcutKeys.assign(keys.begin(), keys.end());
}