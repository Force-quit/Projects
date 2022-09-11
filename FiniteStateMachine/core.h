#pragma once
#include <list>
#include <memory>

class State;

class Transition
{
private:
	std::shared_ptr<State> mNextState;
protected:
	virtual void execTransitingAction(); // permet redéfinition
	virtual void doTransitingAction() = 0; // virtuel pure comme abstact en java
public:
	using TransitionList = std::list<std::shared_ptr<Transition>>;
	Transition(std::shared_ptr<State> nextState = nullptr);
	bool isValid() const; // Aller voir assert
	virtual bool isTransiting() = 0;
	void setNextState(std::shared_ptr<State> nextState);
	std::shared_ptr<State> getNextState() const;
};

class State
{
public:
	using StateList = std::list<std::shared_ptr<State>>;
	struct Parameters
	{
		bool terminal = false;
		bool doInStateActionWhenEntering = false;
		bool doInStateActionWhenExiting = false;
	};

	State(Parameters parameters = Parameters());
	bool isValid() const;
	bool isTerminal() const;
	std::shared_ptr<Transition> isTransiting(); // Aller voir std::optionnal
	void addTransition(Transition& transition);
protected:
	void execEnteringAction();
	void execInStateAction();
	void execExitingAction();
	virtual void doEnteringAction() = 0;
	virtual void doInStateAction() = 0;
	virtual void doExitingAction() = 0;
private:
	Parameters mParameters;
	Transition::TransitionList mTransitions;
};


class FiniteStateMachine
{
public:
	class Layout
	{
	public:
		bool isValid() const;
		std::shared_ptr<State> getInitialState() const;
		void setInitialState(std::shared_ptr<State> initialState);
		void addState(std::shared_ptr<State> state);
		void addStates(State::StateList states);
	private:
		State::StateList mStates;
		std::shared_ptr<State> mInitialState;
	};

	FiniteStateMachine(Layout layout);
private:
	Layout mLayout;
	std::shared_ptr<State> mCurrentState;
	bool mContinue;
};