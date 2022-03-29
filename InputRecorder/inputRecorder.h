#pragma once
#include <vector>
#include <Windows.h>

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
	bool type{true};
	short keyCode{};
	short flags{}; // 2 si up
	long eventPositionInTime{};
	KeyBoardEvent(short keyCode, short flags, long timePos);
	KeyBoardEvent();
};

long record(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyBoardEvent>& keyboardEvents);
void play(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyBoardEvent>& keyboardEvents, long totalTime);
void fillKeyBoardVirtualKeys(std::vector<short>& vector);
void fillMouseVirtualKeys(std::vector<short>& vector);