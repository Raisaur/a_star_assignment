#include "Starchaser.h"
#include "FindStarState.h"
#include <iostream>
#include <vector>

Starchaser::Starchaser(Vector2 pos, Star* star, Grid* grid, SpaceStop* spaceship, SpaceStop* tradingpost) :
	grid_(grid),
	star_(star),
	spaceship_(spaceship),
	tradingpost_(tradingpost)
{
	pathfind_ = new AStarPathfinding(grid_);
	sprite_ = Service<SpriteHandler>::Get()->CreateSprite(STARCHASER_FILE_PATH, 0, 0,
		Config::SCREEN_WIDTH / Config::TILE_COUNT_X, Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y); //64, 64);
	holdingStar_ = false;
	stamina_ = MAX_STAMINA;

	findStarState_ = new FindStarState(this);
	deliverStarState_ = new DeliverStarState(this);
	goHomeState_ = new GoHomeState(this);
	restState_ = new RestState(this);

	AFSM_.AddState(findStarState_);
	AFSM_.AddState(deliverStarState_);
	AFSM_.AddState(goHomeState_);
	AFSM_.AddState(restState_);
	AFSM_.ChangeState("FindStarState");
}

void Starchaser::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { pos_.x_, pos_.y_, sprite_->GetArea().w, sprite_->GetArea().h };
	SDL_RenderCopy(renderer, sprite_->GetTexture(), &sprite_->GetArea(), &dst);
}

void Starchaser::Update(float deltaTime)
{
	AFSM_.Update(deltaTime);
}

bool Starchaser::FollowPath(float deltaTime)
{
	if (!path_.empty())
	{
		MoveTo(path_.top().GetCenter(), deltaTime);

		if (abs((center_ - path_.top().GetCenter()).magnitude()) < 1.0f)
		{
			path_.pop();
		}

		return true;
	}

	return false;
}

void Starchaser::MoveTo(Vector2 target, float deltaTime)
{
	direction_ = target - center_;
	direction_.normalize();
	Vector2 newpos(pos_ + direction_ * MOVE_SPEED * deltaTime);
	SetPosition(newpos);
}

void Starchaser::PickupStar()
{
	int tileIndex = grid_->GetTileIndex(star_->GetCenter());
	grid_->tiles_[tileIndex]->type_ = TileType::EMPTY;
	holdingStar_ = true;
	star_->SetActive(false);
}

void Starchaser::DropStar()
{
	int index = -1;
	if (grid_->tiles_[grid_->GetTileIndex(center_)]->type_ == TileType::EMPTY)
	{
		index = grid_->GetTileIndex(center_);
	}

	else
	{
		std::vector<int> adjacentTileIndices = grid_->GetAdjacentIndices(grid_->GetTileIndex(center_));
		for (int i : adjacentTileIndices)
		{
			if (grid_->tiles_[i]->type_ == TileType::EMPTY)
			{
				index = i;
				break;
			}
		}
	}

	if (index == -1)
	{
		Vector2 temppos = star_->GetSpawnpoint(grid_, TileType::STAR);
		index = grid_->GetTileIndex(temppos);
	}

	star_->SetPosition(grid_->tiles_[index]->pos_);
	star_->SetActive(true);
	holdingStar_ = false;
}

void Starchaser::EmptyPath()
{
	while (!path_.empty())
	{
		path_.pop();
	}
}

void Starchaser::RenderPath(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	SDL_Rect rect;

	std::stack<Tile> tempPath = path_;

	while (!tempPath.empty())
	{
		rect.x = tempPath.top().pos_.x_;
		rect.y = tempPath.top().pos_.y_;
		rect.w = Config::SCREEN_WIDTH / Config::TILE_COUNT_X;
		rect.h = Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y;

		SDL_RenderDrawRect(renderer, &rect);
		tempPath.pop();
	}
}


