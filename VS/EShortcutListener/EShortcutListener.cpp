module;

#include <functional>
#include <vector>
#include <span>

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

void EShortcutListener::waitForKeysToBeReleased()
{
	for (auto& i : shortcutKeys)
	{
		eutilities::waitForKeyRelease(i);
	}
}

std::vector<eutilities::Key> EShortcutListener::targetKeys()
{
	return shortcutKeys;
}

void EShortcutListener::setTargetKeys(std::span<eutilities::Key> keys)
{
	shortcutKeys.assign(keys.begin(), keys.end());
}
