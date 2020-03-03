#include "TEST_STATE_1.h"
#include <iostream>
#include "Service.h"
#include <time.h>
#include "Config.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer* p_renderer)
{
	m_name = "TEST_STATE_1";
	m_renderer = p_renderer;

}

void TEST_STATE_1::Enter()
{
	std::cout << "TEST_STATE_1::Enter" << std::endl;
	std::cout << "Select an object with 1-5 and click on a tile to move it \n1. Obstacle toggle\n2. Spaceship\n3. Tradingpost\n4. Star\n5. Starchaser" << std::endl; 

	srand(time(NULL));
	grid_ = new Grid(Config::TILE_COUNT_X, Config::TILE_COUNT_Y);
	pathFind_ = new AStarPathfinding(grid_);

	spaceship_ = new SpaceStop(EntityType::SPACESHIP, grid_);

	tradingpost_ = new SpaceStop(EntityType::TRADINGPOST, grid_);

	star_ = new Star(grid_);

	starchaser_ = new Starchaser(star_, grid_, spaceship_, tradingpost_);

	timeLastFrame_ = SDL_GetTicks();
	timeNextSense_ = SDL_GetTicks();
	timeNextDecision_ = SDL_GetTicks();
	timeNextAction_ = SDL_GetTicks();

}

bool TEST_STATE_1::Update()
{
	deltaTime_ = (SDL_GetTicks() - timeLastFrame_) * 0.01;
	timeLastFrame_ = SDL_GetTicks();

	SetSelectedEntity();

	if (Service<InputHandler>::Get()->IsMouseButtonPressed(1))
	{
		ReplaceObject();
	}

	starchaser_->Update(deltaTime_);

	Render(m_renderer);

	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}

void TEST_STATE_1::Render(SDL_Renderer* renderer)
{
	grid_->RenderTiles(m_renderer);
	starchaser_->RenderPath(m_renderer);
	star_->Render(m_renderer);
	spaceship_->Render(m_renderer);
	tradingpost_->Render(m_renderer);
	starchaser_->Render(m_renderer);
}

void TEST_STATE_1::SetSelectedEntity()
{
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_1)) selectedEntity_ = SelectedEntity::BLOCK;
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_2)) selectedEntity_ = SelectedEntity::SPACESHIP;
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_3)) selectedEntity_ = SelectedEntity::TRADINGPOST;
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_4)) selectedEntity_ = SelectedEntity::STAR;
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_5)) selectedEntity_ = SelectedEntity::STARCHASER;
}

void TEST_STATE_1::ReplaceObject()
{
	Vector2 mousepos(Service<InputHandler>::Get()->GetMousePositionX(),
		Service<InputHandler>::Get()->GetMousePositionY());
	Tile* tempTile = grid_->tiles_[grid_->GetTileIndex(mousepos)];

	switch (selectedEntity_)
	{
	case SelectedEntity::BLOCK: {
		if (tempTile->type_ == TileType::BLOCKED || tempTile->type_ == TileType::EMPTY)
			tempTile->ToggleBlock();
	}break;


	case SelectedEntity::SPACESHIP: {
		if (tempTile->type_ == TileType::EMPTY)
		{
			int index = grid_->GetTileIndex(spaceship_->GetCenter());
			grid_->tiles_[index]->type_ = TileType::EMPTY;
			spaceship_->SetPosition(tempTile->pos_);
			tempTile->type_ = TileType::SPACESHIP;
		}
	}break;

	case SelectedEntity::TRADINGPOST: {
		if (tempTile->type_ == TileType::EMPTY)
		{
			int index = grid_->GetTileIndex(tradingpost_->GetCenter());
			grid_->tiles_[index]->type_ = TileType::EMPTY;
			tradingpost_->SetPosition(tempTile->pos_);
			tempTile->type_ = TileType::TRADINGPOST;
		}
	}break;

	case SelectedEntity::STAR: {
		if (star_->IsActive())
		{
			if (tempTile->type_ == TileType::EMPTY)
			{
				int index = grid_->GetTileIndex(star_->GetCenter());
				grid_->tiles_[index]->type_ = TileType::EMPTY;
				star_->SetPosition(tempTile->pos_);
				tempTile->type_ = TileType::STAR;
			}
		}
	}break;

	case SelectedEntity::STARCHASER: {
		if (tempTile->type_ == TileType::EMPTY)
		{
			int index = grid_->GetTileIndex(starchaser_->GetCenter());
			grid_->tiles_[index]->type_ = TileType::EMPTY;
			starchaser_->SetPosition(tempTile->pos_);
			tempTile->type_ = TileType::STARCHASER;
		}
	}break;

	default:
		break;
	}

	starchaser_->ReEnterState();
}



