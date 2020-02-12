#ifndef TEST_STATE_1_H
#define TEST_STATE_1_H
#include "State.h"
#include <array>
#include <vector>
#include "SpriteHandler.h"
#include "Sprite.h"
#include "EntityManager.h"

class TEST_STATE_1 : public State
{
	EntityManager em_;

	SDL_Renderer* m_renderer;

	float timeLastFrame_;
	float deltaTime_;

	float timeNextSense_;
	float timeNextDecision_;
	float timeNextAction_;

	void Render(SDL_Renderer* renderer);

public:
	TEST_STATE_1(SDL_Renderer* p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};

#endif // !TEST_STATE_1_H
