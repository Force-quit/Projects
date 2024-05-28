module;

#include <utility>
#include <thread>

export module InvertedMouseMover;

export class InvertedMouseMover 
{
public:
	InvertedMouseMover() = delete;
	
	static void start();
	static void startFor(std::clock_t iActivationTime);
	static void stop();

	[[nodiscard]] static bool isActive();

private:
	static std::pair<int, int> getScreenSize();
	static void mainLoop(std::stop_token iStopToken);
	
	static const std::pair<int, int> mScreenSize;
	inline static std::jthread mLoopThread;
	inline static bool mActive{};
};