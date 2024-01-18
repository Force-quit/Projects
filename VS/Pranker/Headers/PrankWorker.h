#pragma once

import EUtilities;

#include <Windows.h>
#include <array>
#include <chrono>
#include <thread>

class PrankWorker
{
public:
	PrankWorker();
	void start();
	void stop();

private:
	static constexpr auto MIN_PRANK_INTERVAL{ std::chrono::seconds(30).count() };
	static constexpr auto MAX_PRANK_INTERVAL{ std::chrono::minutes(2).count() };
	static constexpr std::array<void (*)(), 2> prankFunctions{
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

	std::jthread loopThread;
	void mainLoop(std::stop_token stoken);
};

