#include "AgentFSM.h"

AgentFSM::AgentFSM() : currentState_(nullptr)
{
}

void AgentFSM::Update(float deltaTime)
{
	if (currentState_ == nullptr)
		return;

	if (!currentState_->Update(deltaTime))
	{
		ChangeState(currentState_->GetNextStateName());
	}
}

void AgentFSM::AddState(AgentState* state)
{
	for (AgentState* s : states_)
	{
		if (s == state)
			return;
	}

	states_.push_back(state);
}

void AgentFSM::ChangeState(std::string statename)
{
	for (AgentState* s : states_)
	{
		if (s->GetName() == statename)
		{
			if (currentState_ != nullptr)
				currentState_->Exit();
			
			currentState_ = s;
			currentState_->Enter();
		}
	}
}
