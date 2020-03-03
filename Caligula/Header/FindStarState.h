#pragma once
#include "AgentFSM.h"

struct FindStarState : public AgentState
{
	FindStarState(Starchaser* agent);
	void Enter();
	bool Update(float deltaTime);
};