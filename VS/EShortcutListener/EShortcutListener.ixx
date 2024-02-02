module;

#include <functional>
#include <vector>
#include <span>
#include <thread>

export module EShortcutListener;
import eutilities;

export class EShortcutListener
{
public:
	EShortcutListener() = delete;

	[[nodiscard]] static std::vector<eutilities::Key> targetKeys();
	static void setTargetKeys(std::span<eutilities::Key> keys);
	static void startListening(std::function<void()> callbackFunc);
	static void stopListening();

private:
	static void mainLoop(std::stop_token iStopToken);
	static void waitForKeysToBeReleased();

	inline static std::vector<eutilities::Key> shortcutKeys;
	inline static std::jthread listenLoop;
	inline static std::function<void()> callbackFunction;
};