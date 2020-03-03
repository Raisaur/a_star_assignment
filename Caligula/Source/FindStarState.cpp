#include "FindStarState.h"
#include "Starchaser.h"
#include <iostream>

FindStarState::FindStarState(Starchaser* agent)
{
	stateName_ = "FindStarState";
	agent_ = agent;
}

void FindStarState::Enter()
{
	std::cout << "findstar state" << std::endl;
	agent_->EmptyPath();
	int startTileIndex = agent_->grid_->GetTileIndex(agent_->GetCenter());
	int goalTileIndex = agent_->grid_->GetTileIndex(agent_->star_->GetCenter());
	if (agent_->pathfind_->FindPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]))
	{
		agent_->path_ = agent_->pathfind_->GetPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]);
	}
}

bool FindStarState::Update(float deltaTime)
{
	if (agent_->GetStamina() <= 0.0f)
	{
		nextStateName_ = "GoHomeState";
		if (agent_->holdingStar_)
			agent_->DropStar();

		return false;
	}

	agent_->FollowPath(deltaTime);

	if (abs((agent_->GetCenter() - agent_->star_->GetCenter()).magnitude()) < 1.0f)
	{
		nextStateName_ = "DeliverStarState";
		agent_->PickupStar();
		return false;
	}

	return true;
}
