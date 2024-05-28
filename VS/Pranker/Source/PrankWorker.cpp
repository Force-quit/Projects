module;

#include <thread>
#include <functional>

module Pranker:PrankWorker;

import :RangedRandomGenerator;

void PrankWorker::start()
{
	mLoopThread = std::jthread(PrankWorker::mainLoop);
}

void PrankWorker::stop()
{
	mLoopThread.request_stop();
}

void PrankWorker::mainLoop(std::stop_token iStopToken)
{
	RangedRandomGenerator<std::size_t> wRandomPrankGenerator(0, mPrankFunctions.size() - 1);
	RangedRandomGenerator<std::clock_t> wRandomIntervalGenerator(MIN_PRANK_INTERVAL, MAX_PRANK_INTERVAL);

	std::clock_t wCurrentTime{ std::clock() };
	std::clock_t wLastPrankTime{ wCurrentTime };
	std::clock_t wRandomInterval{ wRandomIntervalGenerator.random() };

	while (!iStopToken.stop_requested())
	{
		wCurrentTime = std::clock();

		if (wCurrentTime - wLastPrankTime >= wRandomInterval)
		{
			mPrankFunctions[wRandomPrankGenerator.random()]();
			wLastPrankTime = wCurrentTime;
			wRandomInterval = wRandomIntervalGenerator.random();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
