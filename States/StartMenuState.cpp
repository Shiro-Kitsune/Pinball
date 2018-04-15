#include "stdafx.h"
#include "StartMenuState.h"
#include "../GameEngine.h"
#include "IntroGameState.h"
#include "RecordScoreState.h"
#include "../Entity.h"
#include "../Events/Event.h"
#include "../Systems/System.h"
#include "../Systems/UIButtonSystem.h"

StartMenuState StartMenuState::m_startMenuState;

void StartMenuState::Init()
{
	m_entityFactory.ResetIdCounter();

	CreateSystems();
	CreateMainGameUI();

	for (auto& system : m_systems)
	{
		system->Init(*this);
	}
}

void StartMenuState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
	m_eventManager.RemoveAllEvents();
	m_systems.clear();
}

void StartMenuState::HandleEvents(GameEngine & game)
{
	for (auto& event : m_eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::UIEvent)
		{
			continue;
		}

		UIEvent* uiEvent = static_cast<UIEvent*>(event.get());
		if (uiEvent->GetButtonName() == "play_button")
		{
			uiEvent->MarkAsRead();
			game.ChangeState(IntroGameState::Instance());
		}
		else if (uiEvent->GetButtonName() == "score_button")
		{
			uiEvent->MarkAsRead();
			game.PushState(RecordScoreState::Instance());
		}
	}
	m_eventManager.RemoveReadEvents();
}

void StartMenuState::Update(GameEngine & game, float deltaTime)
{
	for (auto& system : m_systems)
	{
		system->Update(deltaTime, *this);
	}
}

void StartMenuState::CreateSystems()
{
	m_systems.push_back(std::make_unique<UIButtonSystem>());
}

void StartMenuState::CreateMainGameUI()
{
	Color color(1.0f, 1.0f, 1.0f);
	Color hoverColor(0.0f, 0.8f, 0.9f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 35.0f, APP_VIRTUAL_HEIGHT - 150.0f), "GLITCH PINBALL!", hoverColor));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 150.0f, APP_VIRTUAL_HEIGHT - 180.0f), "The most unpredictable and frustrating of its kind", Color(0.6f, 0.6f, 0.6f)));
	m_entityManager.AddEntity(m_entityFactory.CreateUIButton(Vector2D(APP_VIRTUAL_WIDTH / 2 - 20.0f, APP_VIRTUAL_HEIGHT / 2 + 90.0f), 120.0f, 30.0f, "Play", color, hoverColor, "play_button"));
	m_entityManager.AddEntity(m_entityFactory.CreateUIButton(Vector2D(APP_VIRTUAL_WIDTH / 2 - 20.0f, APP_VIRTUAL_HEIGHT / 2 + 40.0f), 120.0f, 30.0f, "Best score", color, hoverColor, "score_button"));
}
