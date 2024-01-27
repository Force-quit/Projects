#pragma once

import eutilities;
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
		[]() {eutilities::fullKeyPress(eutilities::Key::WINDOWS); },
		[]() {eutilities::fullKeyPress(eutilities::Key::CAPSLOCK); },
		[]() {InvertedMouseMover::isActive() ? InvertedMouseMover::stop() : InvertedMouseMover::start(); },

		/* Dangerous functions
		[]() {eutilities::fullKeyPress(VK_SPACE); },
		[]() {eutilities::fullKeyPress(VK_RETURN); },
		[]() {eutilities::fullKeyPress(VK_BACK); },
		[]() {eutilities::ctrlV(); },
		[]() {eutilities::fullKeyPress(VK_ESCAPE); }
		*/
	};

	std::jthread mLoopThread;
	void mainLoop(std::stop_token iStopToken);
};

