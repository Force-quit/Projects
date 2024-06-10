module;

#include <thread>
#include <functional>

module Pranker:PasswordWorker;

import eutilities;

void PasswordWorker::start()
{
	mLoopThread = std::jthread([]() 
	{
		while (!passwordIsTyped()) 
		{
			// Nothing to do here
		}
	});
}

void PasswordWorker::waitUntilPasswordIsTyped()
{
	mLoopThread.join();
}

bool PasswordWorker::passwordIsTyped(size_t iNextCharIndex)
{
	bool wAnyKeyWasPressed{};
	bool wRightKeyPressed{};

	while (!wAnyKeyWasPressed)
	{
		for (auto wKey : eutilities::keyboardKeys)
		{
			if (eutilities::isPressed(wKey))
			{
				wAnyKeyWasPressed = true;
				eutilities::waitForKeyRelease(wKey);
				wRightKeyPressed = wKey == mPasswordKeys[iNextCharIndex];
				break;
			}
		}

		eutilities::sleepFor(5);
	}

	if (!wRightKeyPressed)
	{
		return false;
	}

	if (mPasswordKeys.size() == iNextCharIndex + 1)
	{
		return true;
	}

	return passwordIsTyped(iNextCharIndex + 1);
}