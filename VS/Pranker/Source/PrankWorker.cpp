#include "../Headers/PrankWorker.h"
#include "../Headers/RangedRandomGenerator.h"
#include <thread>

PrankWorker::PrankWorker()
	: loopThread()
{
}

void PrankWorker::start()
{
	loopThread = std::jthread(&PrankWorker::mainLoop, this);
}

void PrankWorker::stop()
{
	loopThread.request_stop();
}

void PrankWorker::mainLoop(std::stop_token stoken)
{
	RangedRandomGenerator randomPrankGenerator(0, prankFunctions.size() - 1);
	RangedRandomGenerator randomIntervalGenerator(MIN_PRANK_INTERVAL, MAX_PRANK_INTERVAL);

	std::clock_t lastPrankTime{ std::clock() };
	std::clock_t randomInterval{ randomIntervalGenerator.random() };

	while (!stoken.stop_requested())
	{
		if (std::clock() - lastPrankTime >= randomInterval)
		{
			prankFunctions[randomPrankGenerator.random()]();
			lastPrankTime = std::clock();
			randomInterval = randomIntervalGenerator.random();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
