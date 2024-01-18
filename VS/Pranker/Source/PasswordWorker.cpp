#include "../Headers/PasswordWorker.h"

import EUtilities;
#include <Windows.h>
#include <thread>
#include <functional>

PasswordWorker::PasswordWorker()
	: mLoopThread()
{
}

void PasswordWorker::start()
{
	resetInputBuffer();
	mLoopThread = std::jthread([=]() {while (!passwordIsTyped()) {}});
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
				EUtilities::waitForKeyRelease(wVirtualKey);
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

void PasswordWorker::resetInputBuffer()
{
	for (int wVirtualKey{ 0x01 }; wVirtualKey <= 0xFE; ++wVirtualKey)
		GetAsyncKeyState(wVirtualKey);
}