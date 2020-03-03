#ifndef SPACE_STOP_H
#define SPACE_STOP_H
#include "Entity.h"

constexpr char SPACESHIP_FILE_PATH[] = "../Assets/spaceship.png";
constexpr char TRADINGPOST_FILE_PATH[] = "../Assets/tradingpost.png";

struct SpaceStop : Entity
{
	SpaceStop(Vector2 position, EntityType type)
	{
		SetPosition(position);
		type_ = type;

		if (type_ == EntityType::SPACESHIP)
		{
			sprite_ = Service<SpriteHandler>::Get()->CreateSprite(SPACESHIP_FILE_PATH, 0, 0, 64, 64);
		}

		else if (type_ == EntityType::TRADINGPOST)
		{
			sprite_ = Service<SpriteHandler>::Get()->CreateSprite(TRADINGPOST_FILE_PATH, 0, 0, 64, 64);
		}
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_Rect dst = { pos_.x_, pos_.y_, sprite_->GetArea().w, sprite_->GetArea().h };
		SDL_RenderCopy(renderer, sprite_->GetTexture(), &sprite_->GetArea(), &dst);
	}

};
#endif // !SPACE_STOP_H
