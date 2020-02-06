#ifndef TEST_STATE_1_H
#define TEST_STATE_1_H
#include "State.h"
#include <array>
#include <vector>
#include "Grass.h"

struct SDL_Renderer;
class Sound;
class Grid;


class TEST_STATE_1 : public State
{
	Grid* grid_;
	std::vector<Grass*> grass_;

	SDL_Renderer* m_renderer;
	Sound* m_sound;

	float timeLastFrame_;
	float deltaTime_;

	float timeNextSense_;
	float timeNextDecision_;
	float timeNextAction_;

	void Render(SDL_Renderer* renderer);
	void GenerateGrass();

	int nrOfActions_;
public:
	TEST_STATE_1(SDL_Renderer* p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};

#endif // !TEST_STATE_1_H
