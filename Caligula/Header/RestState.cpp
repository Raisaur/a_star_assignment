#include "RestState.h"
#include "Starchaser.h"
#include <iostream>

RestState::RestState(Starchaser* agent)
{
	stateName_ = "RestState";
	agent_ = agent;
}

void RestState::Enter()
{
	std::cout << "rest state" << std::endl;
}

bool RestState::Update(float deltaTime)
{
	agent_->GainStamina(deltaTime);

	if (agent_->GetStamina() >= MAX_STAMINA)
	{
		nextStateName_ = "FindStarState";
		return false;
	}
}

void RestState::Exit()
{
}
