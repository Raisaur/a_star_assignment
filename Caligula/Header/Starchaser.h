#ifndef STARCHASER_H
#define STARCHASER_H
#include "Entity.h"
#include "star.h"
#include "SpaceStop.h"
#include "A_star.h"
#include "AgentFSM.h"
#include "FindStarState.h"
#include "DeliverStarState.h"
#include "GoHomeState.h"
#include "RestState.h"

constexpr char STARCHASER_FILE_PATH[] = "../Assets/starchaser.png";
constexpr float MAX_STAMINA = 50.0f;
constexpr float STAMINA_DECREASE = 1.0f;
constexpr float MOVE_SPEED = 10.0f;

struct Starchaser : Entity
{
	enum class State
	{
		FIND_STAR,
		DELIVER_STAR,
		GO_HOME,
		DROP_STAR,
		REST
	};

	Starchaser(Star* star, Grid* grid, SpaceStop* spaceship, SpaceStop* tradingpost);
	void Render(SDL_Renderer* renderer);
	void Update(float deltaTime);

	bool FollowPath(float deltaTime);
	void MoveTo(Vector2 target, float deltaTime);

	void PickupStar();
	void DropStar();

	void LoseStamina(float deltaTime) { stamina_ -= STAMINA_DECREASE * deltaTime; };
	void GainStamina(float deltaTime) 
	{ 
		stamina_ += STAMINA_DECREASE * deltaTime * 2; 
		if (stamina_ > MAX_STAMINA)
			stamina_ = MAX_STAMINA;
	};
	float GetStamina() { return stamina_; };

	void EmptyPath();
	void ReEnterState() { AFSM_.ChangeState(AFSM_.GetCurrentStateName()); };
	void RenderPath(SDL_Renderer* renderer);

	Star* star_;
	SpaceStop* spaceship_;
	SpaceStop* tradingpost_;
	Grid* grid_;
	AStarPathfinding* pathfind_;
	std::stack<Tile> path_;

	bool holdingStar_;
private:
	AgentFSM AFSM_;
	AgentState* findStarState_;
	AgentState* deliverStarState_;
	AgentState* goHomeState_;
	AgentState* restState_;

	float stamina_;
	Vector2 direction_;
};

#endif // !STARCHASER_H