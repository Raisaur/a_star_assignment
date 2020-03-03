#include "Tile.h"
#include "Service.h"
#include "SpriteHandler.h"
#include <iostream>

Tile::Tile(int x, int y, int w, int h, int index)
{
	pos_.x_ = x;
	pos_.y_ = y;

	type_ = TileType::BLOCKED;
	sprite_ = Service<SpriteHandler>::Get()->CreateSprite(BLOCKED_FILE_PATH, 0, 0, Config::SCREEN_WIDTH / Config::TILE_COUNT_X, Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y); // w, h);

	tileIndex_ = index;
}

void Tile::Render(SDL_Renderer* renderer) //Redo render conditions
{
	SDL_Rect dst = { pos_.x_, pos_.y_, sprite_->GetArea().w, sprite_->GetArea().h };
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	//SDL_RenderDrawRect(renderer, &dst);
	//SDL_RenderFillRect(renderer, &rect_);

	if(type_ == TileType::BLOCKED)
		SDL_RenderCopy(renderer, sprite_->GetTexture(), &sprite_->GetArea(), &dst);
	
}

void Tile::ToggleBlock()
{
	if (type_ == TileType::BLOCKED)
	{
		type_ = TileType::EMPTY;
	}

	else if (type_ == TileType::EMPTY)
	{
		type_ = TileType::BLOCKED;
		sprite_ = Service<SpriteHandler>::Get()->CreateSprite(BLOCKED_FILE_PATH, 0, 0, Config::SCREEN_WIDTH / Config::TILE_COUNT_X, Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y); // 64, 64);
	}
}

void Tile::SetBlocked(int b)
{
	if (b == 1)
	{
		type_ = TileType::BLOCKED;
		sprite_ = Service<SpriteHandler>::Get()->CreateSprite(BLOCKED_FILE_PATH, 0, 0, Config::SCREEN_WIDTH / Config::TILE_COUNT_X, Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y); //);
	}

	else
	{
		type_ = TileType::EMPTY;
	}
}
