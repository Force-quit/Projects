#define NOMINMAX
#include "../Utilities/utils.h"
#include "inputRecorder.h"
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>


int main()
{
	emile::consoleBundle();

	std::vector<std::thread> keyboardThreads{};
	std::vector<std::vector<short>> keyboardThreadsVKeys{};
	fillKeyBoardVirtualKeys(keyboardThreadsVKeys);

	std::vector<MousePoint> mousePoints{};
	std::vector<MouseEvent> mouseEvents{};
	std::vector<KeyBoardEvent> keyboardEvents{};
	std::mutex keyboardEventsMutex{};

	bool keepRecording = true;

	Sleep(1000);

	std::cout << "Starting recording" << "\n\n";
	clock_t start = std::clock();
	clock_t recordingTime = start - std::clock();
	std::thread mouseMovementRecording(recordMouseMovement, std::ref(mousePoints), std::ref(recordingTime), std::ref(keepRecording));
	std::thread mouseInputRecording(recordMouseEvents, std::ref(mouseEvents), std::ref(recordingTime), std::ref(keepRecording));
	for (auto& vKeysSection : keyboardThreadsVKeys)
		keyboardThreads.push_back(std::thread(recordKeyBoardEvents, std::ref(keyboardEvents), std::ref(keyboardEventsMutex),
			std::ref(vKeysSection), std::ref(recordingTime), std::ref(keepRecording)));


	GetAsyncKeyState(VK_ESCAPE);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
		Sleep(1);
	}

	keepRecording = false;

	mouseMovementRecording.join();
	mouseInputRecording.join();
	for (auto& thread : keyboardThreads)
		thread.join();


	long totalRecordingTime = std::clock() - start;
	std::cout << "Ended recording" << "\n\n";


	if (keyboardEvents.back().keyCode == VK_ESCAPE)
		keyboardEvents.pop_back();

	Sleep(2000);

	std::cout << "Starting playback...";
	play(mousePoints, mouseEvents, keyboardEvents, totalRecordingTime);

	return 0;
}