#include "star.h"
#include "Grid.h"

Star::Star(Grid* grid)
{
	Vector2 position = GetSpawnpoint(grid, TileType::STAR);
	SetPosition(position);
	sprite_ = Service<SpriteHandler>::Get()->CreateSprite(STAR_FILE_PATH, 0, 0, Config::SCREEN_WIDTH / Config::TILE_COUNT_X, Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y); // 64, 64);
	active_ = true;
	grid_ = grid;
}

void Star::Render(SDL_Renderer* renderer)
{
	if (active_)
	{
		SDL_Rect dst = { pos_.x_, pos_.y_, sprite_->GetArea().w, sprite_->GetArea().h };
		SDL_RenderCopy(renderer, sprite_->GetTexture(), &sprite_->GetArea(), &dst);
	}
}

void Star::SetActive(bool active)
{
	active_ = active;
}

void Star::Respawn()
{
	SetPosition(GetSpawnpoint(grid_, TileType::STAR));
	active_ = true;
}
