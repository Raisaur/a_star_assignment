#include "GoHomeState.h"
#include "Starchaser.h"
#include <iostream>

GoHomeState::GoHomeState(Starchaser* agent)
{
	stateName_ = "GoHomeState";
	agent_ = agent;
}

void GoHomeState::Enter()
{
	std::cout << "gohomestate" << std::endl;
	agent_->EmptyPath();
	int startTileIndex = agent_->grid_->GetTileIndex(agent_->GetCenter());
	int goalTileIndex = agent_->grid_->GetTileIndex(agent_->spaceship_->GetCenter());
	if (agent_->pathfind_->FindPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]))
	{
		agent_->path_ = agent_->pathfind_->GetPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]);
	}
}

bool GoHomeState::Update(float deltaTime)
{
	if (agent_->FollowPath(deltaTime))
	{
		return true;
	}

	if (abs((agent_->GetCenter() - agent_->spaceship_->GetCenter()).magnitude()) < 1.0f)
	{
		nextStateName_ = "RestState";
		return false;
	}

	return false;
}

void GoHomeState::Exit()
{
}
