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
	mCallbackFunction = iCallbackFunction;
	stopListening();
	mListenLoop = std::jthread(std::bind_front(&EShortcutListener::mainLoop, this));
}

void EShortcutListener::stopListening()
{
	if (mListenLoop.joinable())
	{
		mListenLoop.request_stop();
		mListenLoop.join();
	}
}

void EShortcutListener::mainLoop(std::stop_token iStopToken)
{
	uint8_t pressedKeys{};
	bool canTrigger{ true };

	while (!iStopToken.stop_requested())
	{
		for (auto i : mShortcutKeys)
		{
			if (eutilities::isPressed(i))
			{
				++pressedKeys;
				if (pressedKeys == mShortcutKeys.size() && canTrigger)
				{
					mCallbackFunction();
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

std::vector<eutilities::Key> EShortcutListener::targetKeys() const
{
	return mShortcutKeys;
}

bool EShortcutListener::isListening() const
{
	return mListenLoop.joinable();
}

void EShortcutListener::setTargetKeys(std::initializer_list<eutilities::Key> iKeys)
{
	mShortcutKeys.assign_range(iKeys);
}

void EShortcutListener::setTargetKeys(std::span<const eutilities::Key> iKeys)
{
	mShortcutKeys.assign_range(iKeys);
}

void EShortcutListener::setTargetKeys(eutilities::Key iKey)
{
	mShortcutKeys.clear();
	mShortcutKeys.emplace_back(iKey);
}