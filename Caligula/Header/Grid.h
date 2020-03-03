#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Vector2.h"
#include "Tile.h"
#include "Config.h"

struct Grid {
	Grid(int horizontalTiles, int verticalTiles);
	void RenderTiles(SDL_Renderer* renderer);

	int GetTileIndex(Vector2 center);
	std::vector<int> GetAdjacentIndices(int tileIndex);

	std::vector<Tile*> tiles_;

	int horizontalTiles_;
	int tileW_, tileH_;
};

#endif // !GRID_H
