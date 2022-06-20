#include "fokenCore.h"
#include <iostream>

void FokinState::doEnteringAction()
{
	std::cout << "Entering da state " << mColor << "!";
}
