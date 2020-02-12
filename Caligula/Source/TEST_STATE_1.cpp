#include "TEST_STATE_1.h"
#include <iostream>
#include "Service.h"
#include <ctime>
#include "Grass.h"
#include "Sheep.h"
#include "Wolf.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer* p_renderer)
{
	m_name = "TEST_STATE_1";
	m_renderer = p_renderer;
}

void TEST_STATE_1::Enter()
{
	std::cout << "TEST_STATE_1::Enter" << std::endl;
	srand(time(NULL));

	em_.GenerateGrid();
	em_.PlaceGrass();
	em_.PlaceSheep();

	timeLastFrame_ = SDL_GetTicks();
	timeNextSense_ = SDL_GetTicks();
	timeNextDecision_ = SDL_GetTicks();
	timeNextAction_ = SDL_GetTicks();
}

bool TEST_STATE_1::Update()
{
	deltaTime_ = SDL_GetTicks() - timeLastFrame_;
	timeLastFrame_ = SDL_GetTicks();

	std::cout << deltaTime_ << std::endl;

	if (timeNextSense_ - timeLastFrame_ <= deltaTime_)
	{
		//std::cout << "Sensing" << std::endl;
		timeNextSense_ = SDL_GetTicks() + deltaTime_ * 30; //sense every 60 frames

		for (int i = 0; i < em_.grass_.size(); i++)
		{
			em_.grass_[i]->Sense();
		}

		for (int i = 0; i < em_.sheep_.size(); i++)
		{
			em_.sheep_[i]->Sense();
		}
	}

	if (timeNextDecision_ - timeLastFrame_ <= deltaTime_)
	{
		//std::cout << "Deciding" << std::endl;
		timeNextDecision_ = SDL_GetTicks() + deltaTime_ * 15; //decide every 30 frames

		for (int i = 0; i < em_.grass_.size(); i++)
		{
			em_.grass_[i]->Decide();
		}

		for (int i = 0; i < em_.sheep_.size(); i++)
		{
			em_.sheep_[i]->Decide();
		}
	}

	if (timeNextAction_ - timeLastFrame_ <= deltaTime_)
	{
		//std::cout << "taking action" << std::endl;
		timeNextAction_ = SDL_GetTicks() + deltaTime_ * 1; //act every 1 frames

		for (int i = 0; i < em_.grass_.size(); i++)
		{
			em_.grass_[i]->Act();
			
			if (em_.grass_[i]->isDead_)
			{
				em_.grass_.erase(em_.grass_.begin() + i);
			}
		}

		for (int i = 0; i < em_.sheep_.size(); i++)
		{
			em_.sheep_[i]->Act();
		}
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
	em_.grid_->RenderTiles(m_renderer);

	for (Grass* grass : em_.grass_)
	{
		grass->Render(m_renderer);
	}

	for (Sheep* sheep : em_.sheep_)
	{
		sheep->Render(m_renderer);
	}
}



