#pragma once

#include <span>
#include <array>
#include <thread>
#include <Windows.h>

class PasswordWorker
{
public:
	PasswordWorker();
	void start();
	void waitUntilPasswordIsTyped();

private:
	static bool passwordIsTyped(size_t iNextCharIndex = 0);
	static void resetInputBuffer();
	
	//emile le hacker
	static constexpr std::array<int, 15> mPasswordKeys
	{
		0x45, 0x4D, 0x49, 0x4C, 0x45,
		VK_SPACE,
		0x4C, 0x45,
		VK_SPACE,
		0x48, 0x41, 0x43, 0x4B, 0x45, 0x52
	};

	std::jthread mLoopThread;
};

