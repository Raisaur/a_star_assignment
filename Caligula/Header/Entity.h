#pragma once 
#include "Vector2.h"
#include "Sprite.h"
#include "SpriteHandler.h"
#include "Config.h"
#include "Service.h"
#include "Grid.h"

enum class EntityType
{
	STARCHASER,
	STAR,
	SPACESHIP,
	TRADINGPOST
};

//  Base Class for all entity types
class Sprite;
struct SDL_Renderer;

class Entity
{
protected:
	Vector2 pos_;
	Vector2 center_;
	Sprite* sprite_;
	EntityType type_;;

public:
	EntityType GetType() { return type_; };
	virtual ~Entity() {};
	Vector2 GetPosition() { return pos_; };
	void SetPosition(Vector2 position) 
	{ 
		pos_ = position; 
		center_.x_ = pos_.x_ + (Config::SCREEN_WIDTH / Config::TILE_COUNT_X) / 2;
		center_.y_ = pos_.y_ + (Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y) / 2;
	};
	Vector2 GetCenter() { return center_; };
	virtual void Render(SDL_Renderer* renderer) {};

	Vector2 GetSpawnpoint(Grid* grid, TileType type) 
	{
		Vector2 newpos;
		bool entitySet = false;
		while (!entitySet)
		{
			int r = rand() % (Config::TILE_COUNT_X * Config::TILE_COUNT_Y);
			if (grid->tiles_[r]->type_ == TileType::EMPTY)
			{
				newpos = grid->tiles_[r]->pos_;
				grid->tiles_[r]->type_ = type;
				entitySet = true;
			}
		}

		return newpos;
	};
};