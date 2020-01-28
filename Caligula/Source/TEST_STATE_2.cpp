#include "TEST_STATE_2.h"
#include "Service.h"
#include "InputHandler.h"
#include <iostream>

TEST_STATE_2::TEST_STATE_2(SDL_Renderer & p_renderer) : m_renderer(&p_renderer)
{
	m_name = "TEST_STATE_2";
}

void TEST_STATE_2::Enter()
{
	std::cout << "TEST_STATE_2::Enter" << std::endl;
}

bool TEST_STATE_2::Update()
{
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_P))
	{
		m_nextState = "TEST_STATE_1";
		return false;
	}

	return true;
}

void TEST_STATE_2::Exit()
{
	std::cout << "TEST_STATE_2::Exit" << std::endl;
}
