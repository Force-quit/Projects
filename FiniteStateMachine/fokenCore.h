#pragma once
#include "core.h"
#include <string>

class FokinState : public State
{
	void doEnteringAction() override; 
	void doInStateAction() override;
	void doExitingAction() override;
	std::string mColor;
public:
	FokinState(std::string color);
};

class FokinTransition : public Transition
{
	void doTransitingAction() override;
	bool isTransiting() override;
};

FiniteStateMachine generateFokinStateMachine();