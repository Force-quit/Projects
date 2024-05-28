module;

#include <array>
#include <thread>

export module Pranker:PasswordWorker;

import eutilities;

export class PasswordWorker
{
public:
	PasswordWorker() = delete;
	static void start();
	static void waitUntilPasswordIsTyped();

private:
	static bool passwordIsTyped(std::size_t iNextCharIndex = 0);
	
	static constexpr auto mPasswordKeys = std::array{
		eutilities::Key::E,
		eutilities::Key::M,
		eutilities::Key::I,
		eutilities::Key::L,
		eutilities::Key::E,
		eutilities::Key::SPACEBAR,
		eutilities::Key::L,
		eutilities::Key::E,
		eutilities::Key::SPACEBAR,
		eutilities::Key::H,
		eutilities::Key::A,
		eutilities::Key::C,
		eutilities::Key::K,
		eutilities::Key::E,
		eutilities::Key::R
	};

	inline static std::jthread mLoopThread;
};