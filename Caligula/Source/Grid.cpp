#include "Grid.h"

#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h" 

Grid::Grid(int horizontalTiles, int verticalTiles)
{
	horizontalTiles_ = horizontalTiles;

	tileW_ = Service<Config>::Get()->SCREEN_WIDTH / horizontalTiles;
	tileH_ = Service<Config>::Get()->SCREEN_HEIGHT / verticalTiles;

	Tile* newTile;
	int tileindex = 0;

	for (int i = 0; i < verticalTiles; i++)
	{
		for (int j = 0; j < horizontalTiles; j++)
		{
			newTile = new Tile(j * tileW_, i * tileH_, tileW_, tileH_, tileindex);
			int r = rand() % 3;
			newTile->SetBlocked(r);

			tiles_.push_back(newTile);
			tileindex++;
		}
	}
}

void Grid::RenderTiles(SDL_Renderer* renderer)
{
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer);
	}
}

int Grid::GetTileIndex(Vector2 center)
{
	int x = center.x_ / tileW_;
	int y = center.y_ / tileH_;
	return(horizontalTiles_ * y + x);
}

std::vector<int> Grid::GetAdjacentIndices(int tileIndex)
{
    std::vector<int> adjacentTileIndices;
    //Top
    if (tileIndex - Config::TILE_COUNT_X < 0) {
        adjacentTileIndices.push_back(tileIndex + Config::TILE_COUNT_X);
        //Right
        if ((tileIndex + 1) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex - 1);
        }
        //Left
        else if ((tileIndex) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex + 1);
        }
        else {
            adjacentTileIndices.push_back(tileIndex - 1);
            adjacentTileIndices.push_back(tileIndex + 1);
        }
    }
    //Bottom
    else if (tileIndex + Config::TILE_COUNT_X >= Config::TILE_COUNT_X * Config::TILE_COUNT_Y) {
        adjacentTileIndices.push_back(tileIndex - Config::TILE_COUNT_X);
        //Right
        if ((tileIndex + 1) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex - 1);
        }
        //Left
        else if ((tileIndex) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex + 1);
        }
        else {
            adjacentTileIndices.push_back(tileIndex - 1);
            adjacentTileIndices.push_back(tileIndex + 1);
        }
    }
    else {
        adjacentTileIndices.push_back(tileIndex + Config::TILE_COUNT_X);
        adjacentTileIndices.push_back(tileIndex - Config::TILE_COUNT_X);
        //Right
        if ((tileIndex + 1) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex - 1);
        }
        //Left
        else if ((tileIndex) % Config::TILE_COUNT_X == 0) {
            adjacentTileIndices.push_back(tileIndex + 1);
        }
        else {
            adjacentTileIndices.push_back(tileIndex - 1);
            adjacentTileIndices.push_back(tileIndex + 1);
        }
    }

    return adjacentTileIndices;
}

