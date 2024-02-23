module;

#include <functional>
#include <vector>
#include <thread>
#include <initializer_list>
#include <type_traits>

export module EShortcutListener;
import eutilities;

template <typename T>
concept IsKey = std::same_as<T, eutilities::Key>;

export class EShortcutListener
{
public:
	EShortcutListener() = delete;

	[[nodiscard]] static std::vector<eutilities::Key> targetKeys();
	[[nodiscard]] static bool isListening();
	static void setTargetKeys(std::initializer_list<eutilities::Key> keys);

	template <std::ranges::input_range Range>
	requires IsKey<std::ranges::range_value_t<Range>>
	static void setTargetKeys(const Range& keys)
	{
		shortcutKeys.assign(keys.begin(), keys.end());
	}

	static void startListening(std::function<void()> callbackFunc);
	static void stopListening();

private:
	static void mainLoop(std::stop_token iStopToken);

	inline static std::vector<eutilities::Key> shortcutKeys;
	inline static std::jthread listenLoop;
	inline static std::function<void()> callbackFunction;
};