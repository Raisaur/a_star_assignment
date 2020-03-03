#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Sprite.h"
#include "Vector2.h"
#include "Config.h"

constexpr char BLOCKED_FILE_PATH[] = "../Assets/asteroid.png";

enum class TileType
{
	EMPTY,
	BLOCKED,
	SPACESHIP,
	TRADINGPOST,
	STAR,
	STARCHASER,
};

struct Tile {

	Tile(int x, int y, int w, int h, int index);
	void Render(SDL_Renderer* renderer);
	void ToggleBlock();
	int GetIndex() { return tileIndex_; };
	Vector2 GetCenter()
	{
		Vector2 center;
		center.x_ = pos_.x_ + (Config::SCREEN_WIDTH / Config::TILE_COUNT_X) / 2;
		center.y_ = pos_.y_ + (Config::SCREEN_HEIGHT / Config::TILE_COUNT_Y) / 2;
		return center;
	};

	void SetBlocked(int b);
	Vector2 pos_;
	TileType type_;
private:
	int tileIndex_;

	Sprite* sprite_;

};

#endif // !TILE_H
