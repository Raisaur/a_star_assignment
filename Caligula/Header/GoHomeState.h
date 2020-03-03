#pragma once

#include "AgentFSM.h"

struct GoHomeState : public AgentState {
	GoHomeState(Starchaser* agent);
	void Enter();
	bool Update(float deltaTime);
	void Exit();
};
