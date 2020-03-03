#ifndef STAR_H
#define STAR_H

#include "Entity.h"

constexpr char STAR_FILE_PATH[] = "../Assets/star.png";

class Grid;

struct Star : Entity{
	Star(Grid* grid_);
	void Render(SDL_Renderer* renderer);
	void SetActive(bool active);
	void Respawn();
	bool IsActive() { return active_; };
private:
	bool active_;
	Grid* grid_;
};

#endif // !STAR_H
