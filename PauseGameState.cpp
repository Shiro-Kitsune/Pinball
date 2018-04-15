#include "stdafx.h"
#include "PauseGameState.h"
#include "UIButtonSystem.h"
#include "GameEngine.h"
#include "StartMenuState.h"
#include "Entity.h"

PauseGameState PauseGameState::m_pauseState;

void PauseGameState::Init()
{
	m_entityFactory.ResetIdCounter();

	CreateSystems();
	CreateUI();

	for (auto& system : m_systems)
	{
		system->Init(*this);
	}
}

void PauseGameState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
	m_eventManager.RemoveAllEvents();
	m_systems.clear();
}

void PauseGameState::HandleEvents(GameEngine & game)
{
	for (auto& event : m_eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::UIEvent)
		{
			continue;
		}

		UIEvent* uiEvent = static_cast<UIEvent*>(event.get());
		if (uiEvent->GetButtonName() == "resume_button")
		{
			game.PopState();
		}
		else if (uiEvent->GetButtonName() == "startMenu_button")
		{
			game.ChangeState(StartMenuState::Instance());
		}
	}
	m_eventManager.RemoveReadEvents();
}

void PauseGameState::Update(GameEngine & game, float deltaTime)
{
	for (auto& system : m_systems)
	{
		system->Update(deltaTime, *this);
	}
}

void PauseGameState::CreateSystems()
{
	m_systems.push_back(std::make_unique<UIButtonSystem>());
}

void PauseGameState::CreateUI()
{
	Color color(1.0f, 1.0f, 1.0f);
	Color hoverColor(0.0f, 0.8f, 0.9f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIButton(Vector2D(APP_VIRTUAL_WIDTH / 2 - 50.0f, APP_VIRTUAL_HEIGHT / 2 + 100.0f), 180.0f, 30.0f, "Resume", color, hoverColor, "resume_button"));
	m_entityManager.AddEntity(m_entityFactory.CreateUIButton(Vector2D(APP_VIRTUAL_WIDTH / 2 - 50.0f, APP_VIRTUAL_HEIGHT / 2 + 20.0f), 180.0f, 30.0f, "Return to Start menu", color, hoverColor, "startMenu_button"));
}