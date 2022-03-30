#include "../Utilities/utils.h"
#include "inputRecorder.h"
#include <Windows.h>
#include <ctime>
#include <iostream>

int main()
{
	emile::disableQuickEdit();

	std::vector<MousePoint> mousePoints{};
	std::vector<MouseEvent> mouseEvents{};
	std::vector<KeyBoardEvent> keyboardEvents{};

	
	Sleep(3000);
	clock_t start = std::clock();
	clock_t recordingTime = start - std::clock();
	bool keepRecording = true;

	std::thread mouseRecording(recordMouseMovement, mousePoints, recordingTime, keepRecording);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = start - std::clock();
		Sleep(1);
	}

	keepRecording = false;

	mouseRecording.join();

	long totalRecordingTime = record(mousePoints, mouseEvents, keyboardEvents);

	Sleep(3000);

	play(mousePoints, mouseEvents, keyboardEvents, totalRecordingTime);

	return 0;
}