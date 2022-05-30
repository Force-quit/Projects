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
	DWORD mouseData{}, dwFlags{};

	MouseEvent(long x, long y, long timePos, DWORD mouseData, DWORD flags);
	MouseEvent();
};

struct KeyboardEvent
{
	bool type{ true };
	short keyCode{};
	short flags{}; // 2 si up
	long eventPositionInTime{};
	KeyboardEvent(short keyCode, short flags, long timePos);
	KeyboardEvent();
};

void recordMouseMovement(std::vector<MousePoint>& mousePoints, const clock_t& recordingTime, const bool& keepRecording);
void recordMouseEvents(std::vector<MouseEvent>& mouseEvents, const clock_t& recordingTime, const bool& keepRecording);
void recordKeyBoardEvents(std::vector<KeyboardEvent>& keyboardEvents, std::mutex& vectorMutex, const std::vector<short>& vKeys, const clock_t& recordingTime, const bool& keepRecording);
void fillKeyBoardVirtualKeys(std::vector<std::vector<short>>& vector);
void fillMouseVirtualKeys(std::vector<short>& vector);
void play(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyboardEvent>& keyboardEvents, long totalTime);

void record();
void loadAndPlay();

void saveTotalRecordingTime(const long& totalRecordingtime);
void loadTotalRecordingTime(long& totalRecordingTime);

void saveMouseMovements(std::vector<MousePoint>& mousePoints);
void loadMouseMovements(std::vector<MousePoint>& mousePoints);

void saveMouseEvents(std::vector<MouseEvent>& mouseEvents);
void loadMouseEvents(std::vector<MouseEvent>& mouseEvents);

void saveKeyBoardEvents(const std::vector<KeyboardEvent>& keyBoardEvents);
void loadKeyboardEvents(std::vector<KeyboardEvent>& keyBoardEvents);