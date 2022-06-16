#pragma once
#include <vector>
class Transition;
class State;
class FiniteStateMachine;

using TransitionList = std::vector<Transition>;
using StateList = std::vector<State>;

class Transition
{
private:
	State* __nextState;
protected:
	void _execTransitingAction();
	void _doTransitingAction();
public:
	Transition(const State* const nextState = nullptr);
	bool isValid() const;
	bool virtual isTransiting() const;
	void setNextState(const State& nextState);
	State getNextState() const;
};

class State 
{
public:
	struct Parameters
	{
		bool terminal = false;
		bool doInStateActionWhenEntering = false;
		bool doInStateActionWhenExiting = false;
	};
	State(Parameters parameters = Parameters());
	bool isValid() const;
	bool isTerminal() const;
	Transition isTransiting() const;
	void addTransition(Transition transition);
private:
	Parameters __parameters;
	TransitionList __transition;
protected:
	void _execEnteringAction();
	void _execInStateAction();
	void _execExitingAction();
	void _doEnteringAction();
	void _doInStateAction();
	void _doExitingAction();
};

class FiniteStateMachine 
{
public:
	class Layout
	{
	public:
		Layout();
		bool isValid() const;
		State* getInitialState() const;
		void setInitialState();
		void addState(State state);
		void addStates(StateList states);
	private:
		StateList __states;
		State* __initialState;
	};

	FiniteStateMachine();
private:
	Layout __layout;
	State* __currentState;
	bool __continue;
};