#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags)
	: Event(time), vkCode(vkCode), dwFlags(dwFlags)
{
}