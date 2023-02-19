#include "KeyboardEventsWorker.h"

// TODO init members

KeyboardEventsWorker::KeyboardEventsWorker(clock_t& currentRecTime, bool& continueListening)
	: currentRecTime(currentRecTime), continueListening(continueListening)

{}

void KeyboardEventsWorker::startListening()
{
	int a = 1;
}

KeyboardEventsWorker::~KeyboardEventsWorker()
{}

std::vector<KeyboardEvent> KeyboardEventsWorker::getKeyboardEvents() const
{
	// TODO return forward list as vector
	return std::vector<KeyboardEvent>();
}
