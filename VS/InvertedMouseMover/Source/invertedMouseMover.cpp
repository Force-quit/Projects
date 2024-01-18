module;

#include <Windows.h>
#include <utility>
#include <thread>
#include <algorithm>

module InvertedMouseMover;

const std::pair<int, int> InvertedMouseMover::mScreenSize{ getScreenSize() };

void InvertedMouseMover::start()
{
	stop();
	mLoopThread = std::jthread(&InvertedMouseMover::mainLoop);
}

void InvertedMouseMover::startFor(clock_t iActivationTime)
{
	stop();
	mLoopThread = std::jthread([=](std::stop_token iStopToken)
	{
		std::jthread wActualMainLoop(&InvertedMouseMover::mainLoop);

		std::clock_t wStartTime{ std::clock() };
		while (std::clock() - wStartTime < iActivationTime && !iStopToken.stop_requested())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

	});
}

bool InvertedMouseMover::isActive()
{
	return mActive;
}

void InvertedMouseMover::stop()
{
	if (mLoopThread.joinable())
	{
		mLoopThread.request_stop();
		mLoopThread.join();
	}
}

std::pair<int, int> InvertedMouseMover::getScreenSize()
{
	RECT windowSize;
	GetWindowRect(GetDesktopWindow(), &windowSize);
	return { windowSize.right - 2, windowSize.bottom - 2 }; // - 2 or else cursor gets stuck
}

void InvertedMouseMover::mainLoop(std::stop_token iStopToken)
{
	mActive = true;
	POINT previousMousePos, mousePos;
	
	GetCursorPos(&mousePos);
	previousMousePos = mousePos;

	while (!iStopToken.stop_requested())
	{
		GetCursorPos(&mousePos);

		if (mousePos.x != previousMousePos.x || mousePos.y != previousMousePos.y)
		{
			mousePos.x += 2 * (previousMousePos.x - mousePos.x);
			mousePos.y += 2 * (previousMousePos.y - mousePos.y);

			mousePos.x = std::clamp(static_cast<int>(mousePos.x), 2, mScreenSize.first);
			mousePos.y = std::clamp(static_cast<int>(mousePos.y), 2, mScreenSize.second);

			SetCursorPos(mousePos.x, mousePos.y);
			previousMousePos = mousePos;
		}
	}
	mActive = false;
}