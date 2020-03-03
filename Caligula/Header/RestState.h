#pragma once

#include "AgentFSM.h"

struct RestState : public AgentState {
	RestState(Starchaser* agent);
	void Enter();
	bool Update(float deltaTime);
	void Exit();
};