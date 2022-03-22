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

struct KeyBoardEvent
{
	bool type{}; // 1 keyboard 0 mouse
	short keyCode{};
	short flags{}; // 2 si up
	long eventPositionInTime{};
	KeyBoardEvent(bool type, short keyCode, short flags, long timePos);
	KeyBoardEvent();
};

long record(std::vector<MousePoint>& mousePoints, std::vector<KeyBoardEvent>& keyboardEvents, std::vector<short>& vKeys);
void play(std::vector<MousePoint>& mousePoints, std::vector<KeyBoardEvent>& keyboardEvents, long totalTime);
void fillVirtualKeys(std::vector<short>& vector);