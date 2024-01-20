#pragma once

import eUtilities;
import InvertedMouseMover;

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
	static constexpr std::array<void (*)(), 3> mPrankFunctions
	{
		[]() {eUtilities::fullKeyPress(VK_LWIN); },
		[]() {eUtilities::fullKeyPress(VK_CAPITAL); },
		[]() {InvertedMouseMover::isActive() ? InvertedMouseMover::stop() : InvertedMouseMover::start(); },

		/* Dangerous functions
		[]() {eUtilities::fullKeyPress(VK_SPACE); },
		[]() {eUtilities::fullKeyPress(VK_RETURN); },
		[]() {eUtilities::fullKeyPress(VK_BACK); },
		[]() {eUtilities::ctrlV(); },
		[]() {eUtilities::fullKeyPress(VK_ESCAPE); }
		*/
	};

	std::jthread mLoopThread;
	void mainLoop(std::stop_token iStopToken);
};

