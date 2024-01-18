#pragma once

import EUtilities;

#include <Windows.h>
#include <array>
#include <thread>

class PrankWorker
{
public:
	PrankWorker();
	void start();
	void stop();

private:
	static constexpr int MIN_PRANK_INTERVAL{ 30000 };
	static constexpr int MAX_PRANK_INTERVAL{ 120000 };
	static constexpr std::array<void (*)(), 2> mPrankFunctions
	{
		[]() {EUtilities::fullKeyPress(VK_LWIN); },
		[]() {EUtilities::fullKeyPress(VK_CAPITAL); },

		/* Dangerous functions
		[]() {EUtilities::fullKeyPress(VK_SPACE); },
		[]() {EUtilities::fullKeyPress(VK_RETURN); },
		[]() {EUtilities::fullKeyPress(VK_BACK); },
		[]() {EUtilities::ctrlV(); },
		[]() {EUtilities::fullKeyPress(VK_ESCAPE); }
		*/
	};

	std::jthread mLoopThread;
	void mainLoop(std::stop_token iStopToken);
};

