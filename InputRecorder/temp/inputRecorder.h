#pragma once
#include <Windows.h>
#include <mutex>
#include <vector>

struct MousePoint
{
	POINT p{};
	long eventPositionInTime{};
	MousePoint(POINT& currentPoint, long timePos);
	MousePoint();
};

struct MouseEvent
{
	long x{}, y{}, eventPositionInTime{};
	bool type{ false };
	DWORD mouseData{}, dwFlags{};

	MouseEvent(long x, long y, long timePos, DWORD mouseData, DWORD flags);
	MouseEvent();
};

struct KeyBoardEvent
{
	bool type{ true };
	short keyCode{};
	short flags{}; // 2 si up
	long eventPositionInTime{};
	KeyBoardEvent(short keyCode, short flags, long timePos);
	KeyBoardEvent();
};

void recordMouseMovement(std::vector<MousePoint>& mousePoints, const clock_t& recordingTime, const bool& keepRecording);
void recordMouseEvents(std::vector<MouseEvent>& mouseEvents, const clock_t& recordingTime, const bool& keepRecording);
void recordKeyBoardEvents(std::vector<KeyBoardEvent>& keyboardEvents, std::mutex& vectorMutex, const std::vector<short>& vKeys, const clock_t& recordingTime, const bool& keepRecording);
void fillKeyBoardVirtualKeys(std::vector<std::vector<short>>& vector);
void fillMouseVirtualKeys(std::vector<short>& vector);
void play(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyBoardEvent>& keyboardEvents, long totalTime);
