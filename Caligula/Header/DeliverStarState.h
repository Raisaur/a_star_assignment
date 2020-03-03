#pragma once

#include "AgentFSM.h"

struct DeliverStarState : public AgentState{
	DeliverStarState(Starchaser* agent);
	void Enter();
	bool Update(float deltaTime);
	void Exit();
};
