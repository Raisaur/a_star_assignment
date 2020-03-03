#include "DeliverStarState.h"
#include "Starchaser.h"
#include <iostream>

DeliverStarState::DeliverStarState(Starchaser* agent)
{
	stateName_ = "DeliverStarState";
	agent_ = agent;
}

void DeliverStarState::Enter()
{
	std::cout << "deliver star state" << std::endl;
	agent_->EmptyPath();
	int startTileIndex = agent_->grid_->GetTileIndex(agent_->GetCenter());
	int goalTileIndex = agent_->grid_->GetTileIndex(agent_->tradingpost_->GetCenter());
	if (agent_->pathfind_->FindPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]))
	{
		agent_->path_ = agent_->pathfind_->GetPath(*agent_->grid_->tiles_[startTileIndex], *agent_->grid_->tiles_[goalTileIndex]);
	}
}

bool DeliverStarState::Update(float deltaTime)
{
	agent_->LoseStamina(deltaTime);

	if (agent_->GetStamina() <= 0.0f)
	{
		nextStateName_ = "GoHomeState";
		agent_->DropStar();
		return false;
	}

	if (agent_->FollowPath(deltaTime))
	{
		return true;
	}

	if (abs((agent_->GetCenter() - agent_->tradingpost_->GetCenter()).magnitude()) < 1.0f)
	{
		nextStateName_ = "FindStarState";
		agent_->star_->Respawn();
		agent_->holdingStar_ = false;
		return false;
	}

	return false;
}

void DeliverStarState::Exit()
{

}
