#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"

#include "Grid.h"
#include "Grass.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer* p_renderer)
{
	m_name = "TEST_STATE_1";
	m_renderer = p_renderer;
}

void TEST_STATE_1::Enter()
{
	std::cout << "TEST_STATE_1::Enter" << std::endl;

	timeLastFrame_ = SDL_GetTicks();

	grid_ = new Grid(10, 10, "../Assets/dirt.png");
	GenerateGrass();
}

bool TEST_STATE_1::Update()
{
	deltaTime_ = SDL_GetTicks() - timeLastFrame_;
	timeLastFrame_ = SDL_GetTicks();

	if (timeNextSense_ - timeLastFrame_ <= deltaTime_)
	{
		//std::cout << "Sensing" << std::endl;
		timeNextSense_ = SDL_GetTicks() + deltaTime_ * 120; //sense every 60 frames

		for (Grass* grass : grass_)
		{
			grass->Sense();
		}
	}

	if (timeNextDecision_ - timeLastFrame_ <= deltaTime_)
	{
		//std::cout << "Deciding" << std::endl;
		timeNextDecision_ = SDL_GetTicks() + deltaTime_ * 60; //sense every 60 frames

		for (Grass* grass : grass_)
		{
			grass->Decide();
		}
	}

	if (timeNextAction_ - timeLastFrame_ <= deltaTime_)
	{
		nrOfActions_++;
		//std::cout << "taking action" << std::endl;
		timeNextAction_ = SDL_GetTicks() + deltaTime_ * 30; //sense every 60 frames

		for (Grass* grass : grass_)
		{
			//std::cout << grass->tileIndex_ << std::endl;
			grass->Act();
		}

		/*for (int i = 0; i < grass_.size(); i++)
		{
			grass_[i]->Act();
		}*/
	}

	Render(m_renderer);

	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}

void TEST_STATE_1::Render(SDL_Renderer* renderer)
{
	grid_->RenderTiles(m_renderer);

	for (Grass* grass : grass_)
	{
		grass->Render(m_renderer);
	}
}

void TEST_STATE_1::GenerateGrass()
{
	int grassTiles[10];
	int tileNr;
	int startHealth;

	srand(NULL);
	for (int i = 0; i < 3; i++)
	{ 
		tileNr = rand() % 100;

		if (grid_->tiles_[tileNr]->grass_ == nullptr)
		{
			startHealth = rand() % 12 + 1;
			Grass* newGrass = new Grass("../Assets/grass.png", grid_, &grass_, tileNr, i + 1);
			grass_.push_back(newGrass);
		}
	}
}

