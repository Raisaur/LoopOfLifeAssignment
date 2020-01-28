#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer)
{
	m_name = "TEST_STATE_1";
}

void TEST_STATE_1::Enter()
{
	std::cout << "TEST_STATE_1::Enter" << std::endl;

	grid_ = new Grid(10, 10, 32, "../Assets/dirt.png");
}

bool TEST_STATE_1::Update()
{
	m_timer++;

	grid_->RenderTiles(m_renderer);
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
