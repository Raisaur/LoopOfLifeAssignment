#pragma once

#include "State.h"
#include <array>

#include "Grid.h"

struct SDL_Renderer;
class Sound;

class TEST_STATE_1 : public State
{
	Grid* grid_;

	SDL_Renderer* m_renderer;
	Sound* m_sound;
	int m_timer;
public:
	TEST_STATE_1(SDL_Renderer* p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};
