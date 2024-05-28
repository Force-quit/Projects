module;

#include <Windows.h>
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
		for (int wVirtualKey{ 0x01 }; wVirtualKey <= 0xFE; ++wVirtualKey)
		{
			if (GetAsyncKeyState(wVirtualKey))
			{
				wAnyKeyWasPressed = true;
				eutilities::waitForKeyRelease(static_cast<eutilities::Key>(wVirtualKey));
				wRightKeyPressed = wVirtualKey == mPasswordKeys[iNextCharIndex];
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	if (!wRightKeyPressed)
		return false;

	if (mPasswordKeys.size() == iNextCharIndex + 1)
		return true;

	return passwordIsTyped(iNextCharIndex + 1);
}