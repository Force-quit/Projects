module;

#include <functional>
#include <vector>
#include <thread>
#include <initializer_list>
#include <span>

export module EShortcutListener;

import eutilities;

export class EShortcutListener
{
public:
	EShortcutListener() = delete;

	[[nodiscard]] static std::vector<eutilities::Key> targetKeys();
	[[nodiscard]] static bool isListening();

	static void setTargetKeys(std::initializer_list<eutilities::Key> iKeys);
	static void setTargetKeys(const eutilities::Key iKey);
	static void setTargetKeys(std::span<const eutilities::Key> iKeys);

	static void startListening(std::function<void()> iCallbackFunction);
	static void stopListening();

private:
	static void mainLoop(std::stop_token iStopToken);

	inline static std::vector<eutilities::Key> sShortcutKeys;
	inline static std::jthread sListenLoop;
	inline static std::function<void()> sCallbackFunction;
};