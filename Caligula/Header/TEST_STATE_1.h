#ifndef TEST_STATE_1_H
#define TEST_STATE_1_H
#include "State.h"
#include <array>
#include <vector>
#include "Grid.h"
#include "InputHandler.h"
#include "A_star.h"
#include "Star.h"
#include "SpaceStop.h"
#include "Starchaser.h"

class TEST_STATE_1 : public State
{
	enum class SelectedEntity {
		BLOCK,
		SPACESHIP,
		TRADINGPOST,
		STAR,
		STARCHASER
	};

	void Render(SDL_Renderer* renderer);
	void SetSelectedEntity();
	void ReplaceObject();
	SelectedEntity selectedEntity_;

	SDL_Renderer* m_renderer;

	Grid* grid_;
	AStarPathfinding* pathFind_;
	std::stack<Tile> path_;

	float timeLastFrame_;
	float deltaTime_;

	float timeNextSense_;
	float timeNextDecision_;
	float timeNextAction_;

	Starchaser* starchaser_;
	Star* star_;
	SpaceStop* spaceship_;
	SpaceStop* tradingpost_;
	
public:
	TEST_STATE_1(SDL_Renderer* p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};

#endif // !TEST_STATE_1_H
