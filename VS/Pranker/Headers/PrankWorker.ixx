module;

#include <array>
#include <thread>

export module Pranker:PrankWorker;

import eutilities;
import InvertedMouseMover;

export class PrankWorker
{
public:
	PrankWorker() = delete;
	static void start();
	static void stop();

private:
	static void mainLoop(std::stop_token iStopToken);

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

	inline static std::jthread mLoopThread;
};

