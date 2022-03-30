#include "../Utilities/utils.h"
#include "inputRecorder.h"
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <thread>

int main()
{
	emile::disableQuickEdit();

	std::vector<MousePoint> mousePoints{};
	std::vector<MouseEvent> mouseEvents{};
	std::vector<KeyBoardEvent> keyboardEvents{};

	//std::vector<short> stuff = std::vector<short>(keyBoardVKeys.begin(), keyBoardVKeys.begin() + 3);
	//std::vector<short> stuff2 = std::vector<short>(keyBoardVKeys.begin() + 3, keyBoardVKeys.begin() + 6);

	Sleep(3000);
	clock_t start = std::clock();
	clock_t recordingTime = start - std::clock();
	bool keepRecording = true;

	std::cout << "Starting recording" << std::endl;
	std::thread mouseMovementRecording(recordMouseMovement, std::ref(mousePoints), std::ref(recordingTime), std::ref(keepRecording));
	std::thread mouseInputRecording(recordMouseEvents, std::ref(mouseEvents), std::ref(recordingTime), std::ref(keepRecording));
	std::thread keyboardInputRecording(recordKeyBoardEvents, std::ref(keyboardEvents), std::ref(recordingTime), std::ref(keepRecording));

	GetAsyncKeyState(VK_ESCAPE);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
		Sleep(1);
	}

	keepRecording = false;

	mouseMovementRecording.join();
	mouseInputRecording.join();
	keyboardInputRecording.join();

	long totalRecordingTime = std::clock() - start;
	std::cout << "Ended recording" << std::endl;

	Sleep(3000);

	if (keyboardEvents.back().keyCode == VK_ESCAPE)
		keyboardEvents.pop_back();

	play(mousePoints, mouseEvents, keyboardEvents, totalRecordingTime);

	return 0;
}