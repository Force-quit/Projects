#include "core.h"
#include <stdexcept>

void Transition::execTransitingAction()
{
	doTransitingAction();
}

Transition::Transition(std::shared_ptr<State> nextState)
	: mNextState(nextState)
{
}

bool Transition::isValid() const
{
	return mNextState != nullptr;
}

void Transition::setNextState(std::shared_ptr<State> nextState)
{
	mNextState = nextState;
}

std::shared_ptr<State> Transition::getNextState() const
{
	return mNextState;
}

State::State(Parameters parameters)
	: mParameters(parameters)
{
}

bool State::isValid() const
{
	if (isTerminal())
		return true;

	for (auto& t : mTransitions)
		if (!t.get()->isValid())
			return false;

	return true;
}

bool State::isTerminal() const
{
	return mParameters.terminal;
}

std::shared_ptr<Transition> State::isTransiting() 
{
	for (auto& t : mTransitions)
		if (t.get()->isTransiting())
			return t;
	return nullptr;
}

void State::addTransition(Transition& transition)
{
	mTransitions.push_back(std::make_shared<Transition>(transition));
}

void State::execEnteringAction()
{
	doEnteringAction();
	if (mParameters.doInStateActionWhenEntering)
		execInStateAction();
}

void State::execInStateAction()
{
	doInStateAction();
}

void State::execExitingAction()
{
	doExitingAction();
	if (mParameters.doInStateActionWhenExiting)
		execInStateAction();
}

FiniteStateMachine::FiniteStateMachine(Layout layout)
	: mLayout(layout), mCurrentState(layout.getInitialState()), mContinue(true)
{
	if (!layout.isValid())
		throw std::invalid_argument("State machine's layout is invalid");
}

bool FiniteStateMachine::Layout::isValid() const
{
	if (mStates.size() == 0)
		return false;
	for (auto& state : mStates)
		if (!state.get()->isValid())
			return false;
	return true;
}

std::shared_ptr<State> FiniteStateMachine::Layout::getInitialState() const
{
	return mInitialState;
}

void FiniteStateMachine::Layout::setInitialState(std::shared_ptr<State> initialState)
{
	mInitialState = initialState;
}

void FiniteStateMachine::Layout::addState(std::shared_ptr<State> state)
{
	mStates.push_back(state);
}

void FiniteStateMachine::Layout::addStates(State::StateList states)
{
	mStates.splice(mStates.end(), states);
}
