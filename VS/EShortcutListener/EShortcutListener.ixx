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
	[[nodiscard]] std::vector<eutilities::Key> targetKeys() const;
	[[nodiscard]] bool isListening() const;

	void setTargetKeys(std::initializer_list<eutilities::Key> iKeys);
	void setTargetKeys(const eutilities::Key iKey);
	void setTargetKeys(std::span<const eutilities::Key> iKeys);

	void startListening(std::function<void()> iCallbackFunction);
	void stopListening();

private:
	void mainLoop(std::stop_token iStopToken);

	std::vector<eutilities::Key> mShortcutKeys;
	std::jthread mListenLoop;
	std::function<void()> mCallbackFunction;
};