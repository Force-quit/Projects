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

	long totalRecordingTime = record(mousePoints, mouseEvents, keyboardEvents);

	Sleep(3000);

	play(mousePoints, mouseEvents, keyboardEvents, totalRecordingTime);

	return 0;
}