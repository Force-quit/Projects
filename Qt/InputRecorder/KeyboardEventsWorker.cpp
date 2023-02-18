#include "KeyboardEventsWorker.h"

KeyboardEventsWorker::KeyboardEventsWorker(clock_t& currentRecTime, bool& continueListening)
	: currentRecTime(currentRecTime), continueListening(continueListening)

{}

void KeyboardEventsWorker::startListening()
{
	int a = 1;
}

KeyboardEventsWorker::~KeyboardEventsWorker()
{}