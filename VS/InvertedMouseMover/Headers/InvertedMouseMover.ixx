module;

#include <utility>
#include <thread>
#include <string>
#include <functional>

export module InvertedMouseMover;

export class InvertedMouseMover 
{
public:
	InvertedMouseMover() = delete;
	static void start();
	static void startFor(clock_t iActivationTime);
	static void stop();

private:
	static std::pair<int, int> getScreenSize();
	static void mainLoop(std::stop_token iStopToken);
	
	static const std::pair<int, int> mScreenSize;
	inline static std::jthread mLoopThread;
};