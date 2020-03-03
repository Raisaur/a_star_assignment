#include "A_star.h"

AStarNode::AStarNode()
{
    f_ = g_ = h_ = 0;
    positionTile_ = nullptr;
    parentNode_ = nullptr;
}

void AStarNode::ResetNode()
{
    f_ = g_ = h_ = 0;
    parentNode_ = nullptr;
}

AStarPathfinding::AStarPathfinding(Grid* grid)
{
    grid_ = grid; // Remove before handin
    for (int i = 0; i < sizeof(nodeArray_) / sizeof(nodeArray_[0]); i++)
    {
        nodeArray_[i].SetTile(grid->tiles_[i]);
    }
}

bool AStarPathfinding::FindPath(Tile startTile, Tile goalTile)
{
    ResetNodes();
    Tile currentTile = startTile;
    Vector2 goalPoint(goalTile.GetIndex() % Config::TILE_COUNT_X, goalTile.GetIndex() / Config::TILE_COUNT_X);

    openList_.push_back(SetNode(currentTile, goalPoint, nullptr));

    while (!openList_.empty())
    {
        if (currentTile.GetIndex() == goalTile.GetIndex())
        {
            return true;
        }


        closedList_.push_back(nodeArray_[currentTile.GetIndex()]);
        openList_.erase(openList_.begin() + GetNodeIndex(nodeArray_[currentTile.GetIndex()], openList_));

        std::vector <int> adjacentIndices = GetAdjacentIndices(currentTile.GetIndex());
        {
            for (int& index : adjacentIndices)
            {
                if (nodeArray_[index].GetTile()->type_ == TileType::BLOCKED) continue;

                if (IsNodeInVector(nodeArray_[index], openList_)) continue;

                if (IsNodeInVector(nodeArray_[index], closedList_)) continue;

                openList_.push_back(SetNode(*nodeArray_[index].GetTile(), goalPoint, &nodeArray_[currentTile.GetIndex()]));
            }
        }

        int lowestFCost = INT_MAX;
        int lowestHCost = INT_MAX;

        for (AStarNode& node : openList_)
        {
            if (node.GetFCost() < lowestFCost)
            {
                lowestFCost = node.GetFCost();
                currentTile = *node.GetTile();
            }

            else if (node.GetFCost() == lowestFCost)
            {
                if (node.GetHCost() < lowestHCost)
                {
                    lowestHCost = node.GetHCost();
                    currentTile = *node.GetTile();
                }
            }
        }
    }

    return false;
}


std::stack<Tile> AStarPathfinding::GetPath(Tile startTile, Tile targetTile)
{
    Tile currentTile = targetTile;
    std::stack<Tile> path;

    while (nodeArray_[currentTile.GetIndex()].GetParentNode() != nullptr)
    {
        path.push(currentTile);
        currentTile = *nodeArray_[currentTile.GetIndex()].GetParentNode()->GetTile();
    }

    path.push(startTile);

    return path;
}

AStarNode AStarPathfinding::SetNode(Tile currentTile, Vector2 goalPoint, AStarNode* parent)
{
    Vector2 currentPoint = FindCoord(currentTile);

    int xCost = abs(currentPoint.x_ - goalPoint.x_) * Config::TRAVEL_COST;
    int yCost = abs(currentPoint.y_ - goalPoint.y_) * Config::TRAVEL_COST;
    nodeArray_[currentTile.GetIndex()].SetHCost(xCost + yCost);

    nodeArray_[currentTile.GetIndex()].SetParentNode(parent);
    if (parent != nullptr)
    {
        nodeArray_[currentTile.GetIndex()].SetGCost(parent->GetGCost() + Config::TRAVEL_COST);
    }

    nodeArray_[currentTile.GetIndex()].SetFCost();

    return nodeArray_[currentTile.GetIndex()];
}

Vector2 AStarPathfinding::FindCoord(Tile tile)
{
    Vector2 currentPoint(tile.GetIndex() % Config::TILE_COUNT_X, tile.GetIndex() / Config::TILE_COUNT_X);
    return currentPoint;
}

bool AStarPathfinding::IsNodeInVector(AStarNode node, std::vector<AStarNode> vector)
{
    for (AStarNode& n : vector)
    {
        if (n.GetTile()->GetIndex() == node.GetTile()->GetIndex())
            return true;
    }
    return false;
}

int AStarPathfinding::GetNodeIndex(AStarNode node, std::vector<AStarNode> vector)
{
    int i = 0;
    for (AStarNode& n : vector)
    {
        if (n.GetTile()->GetIndex() == node.GetTile()->GetIndex())
            break;

        i++;
    }
    return i;
}

std::vector<int> AStarPathfinding::GetAdjacentIndices(int tileIndex)
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

void AStarPathfinding::ResetNodes()
{
    openList_.clear();
    closedList_.clear();

    for (AStarNode node : nodeArray_)
    {
        node.ResetNode();
    }
}
