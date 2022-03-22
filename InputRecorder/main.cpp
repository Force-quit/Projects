#include "../Utilities/utils.h"
#include "inputRecorder.h"
#include <Windows.h>
#include <ctime>
#include <iostream>

int main()
{
	emile::disableQuickEdit();
	std::vector<short> vKeys{};
	fillVirtualKeys(vKeys);

	std::vector<MousePoint> mousePoints{};
	std::vector<KeyBoardEvent> keyboardEvents{};

	long totalRecordingTime = record(mousePoints, keyboardEvents, vKeys);

	Sleep(3000);

	play(mousePoints, keyboardEvents, totalRecordingTime);

	return 0;
}