#ifndef A_STAR_H
#define A_STAR_H
#include <stack>
#include "Grid.h"

struct AStarNode {
	AStarNode();

	int GetFCost() { return f_; };
	int GetGCost() { return g_; };
	int GetHCost() { return h_; };

	void SetFCost() { f_ = g_ + h_; };
	void SetGCost(int g) { g_ = g; };
	void SetHCost(int h) { h_ = h; };

	Tile* GetTile() { return positionTile_; };
	void SetTile(Tile* tile) { positionTile_ = tile; };

	AStarNode* GetParentNode() { return parentNode_; };
	void SetParentNode(AStarNode* node) { parentNode_ = node; };

	void ResetNode();
private:
	int f_, g_, h_;

	Tile* positionTile_;
	AStarNode* parentNode_;
};

struct AStarPathfinding {
	AStarPathfinding(Grid* grid);
	bool FindPath(Tile startTile, Tile goalTile);
	std::stack<Tile> GetPath(Tile currentTile, Tile TargetTile);
private:
	AStarNode SetNode(Tile currentTile, Vector2 goalPos, AStarNode* parent);
	Vector2 FindCoord(Tile tile);
	bool IsNodeInVector(AStarNode node, std::vector<AStarNode> vector);
	int GetNodeIndex(AStarNode node, std::vector<AStarNode> vector);
	std::vector<int> GetAdjacentIndices(int tileIndex);
	void ResetNodes();

	std::vector<AStarNode> openList_;
	std::vector<AStarNode> closedList_;
	AStarNode nodeArray_[Config::TILE_COUNT_X * Config::TILE_COUNT_Y];

	Grid* grid_;
};

#endif // !A_STAR_H

