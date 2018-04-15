#include "stdafx.h"
#include "GameEngine.h"
#include "GameState.h"
#include "StartMenuState.h"

void GameEngine::Init()
{
	ChangeState(StartMenuState::Instance());
}

void GameEngine::Cleanup()
{
	//Cleanup all states
	while (!m_states.empty())
	{
		PopState();
	}
}

void GameEngine::ChangeState(GameState * state)
{
	if (state == nullptr)
	{
		std::cerr << "State is null." << std::endl;
		return;
	}

	//Cleanup the current states
	Cleanup();

	//Store and initialize the new state
	m_states.push_back(state);
	m_states.back()->Init();
}

void GameEngine::PushState(GameState * state)
{
	if (state == nullptr)
	{
		std::cerr << "State is null." << std::endl;
		return;
	}

	m_states.push_back(state);
	m_states.back()->Init();
}

void GameEngine::PopState()
{
	if (!m_states.empty())
	{
		m_states.back()->Cleanup();
		m_states.pop_back();
	}
}

void GameEngine::HandleEvents()
{
	m_states.back()->HandleEvents(*this);
}

void GameEngine::Update(const float deltaTime)
{
	m_states.back()->Update(*this, deltaTime);
}

void GameEngine::Render()
{
	m_states.back()->Render();
}