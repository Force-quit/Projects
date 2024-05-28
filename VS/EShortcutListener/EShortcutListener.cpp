module;

#include <functional>
#include <vector>
#include <initializer_list>
#include <span>
#include <thread>

module EShortcutListener;

import eutilities;

void EShortcutListener::startListening(std::function<void()> iCallbackFunction)
{
	sCallbackFunction = iCallbackFunction;
	stopListening();
	sListenLoop = std::jthread(&EShortcutListener::mainLoop);
}

void EShortcutListener::stopListening()
{
	if (sListenLoop.joinable())
	{
		sListenLoop.request_stop();
		sListenLoop.join();
	}
}

void EShortcutListener::mainLoop(std::stop_token iStopToken)
{
	uint8_t pressedKeys{};
	bool canTrigger{ true };

	while (!iStopToken.stop_requested())
	{
		for (auto i : sShortcutKeys)
		{
			if (eutilities::isPressed(i))
			{
				++pressedKeys;
				if (pressedKeys == sShortcutKeys.size() && canTrigger)
				{
					sCallbackFunction();
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
	return sShortcutKeys;
}

bool EShortcutListener::isListening()
{
	return sListenLoop.joinable();
}

void EShortcutListener::setTargetKeys(std::initializer_list<eutilities::Key> iKeys)
{
	sShortcutKeys.assign_range(iKeys);
}

void EShortcutListener::setTargetKeys(std::span<const eutilities::Key> iKeys)
{
	sShortcutKeys.assign_range(iKeys);
}

void EShortcutListener::setTargetKeys(eutilities::Key iKey)
{
	sShortcutKeys.clear();
	sShortcutKeys.emplace_back(iKey);
}