#pragma once
#include <vector>
#include <string>

class Starchaser;

struct AgentState {
	virtual void Enter() {};
	virtual bool Update(float deltaTime) = 0;
	virtual void Exit() {};

	std::string GetName() { return stateName_; };
	std::string GetNextStateName() { return nextStateName_; };

	
protected:
	std::string stateName_;
	std::string nextStateName_;

	Starchaser* agent_;
};

struct AgentFSM {
	AgentFSM();
	void Update(float deltaTime);
	void AddState(AgentState* state);
	void ChangeState(std::string statename);

	std::string GetCurrentStateName() { return currentState_->GetName(); };

private:
	std::vector<AgentState*> states_;
	AgentState* currentState_;
};