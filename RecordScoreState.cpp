#include "stdafx.h"
#include "RecordScoreState.h"
#include "GameEngine.h"
#include "Entity.h"
#include "UIButtonSystem.h"

RecordScoreState RecordScoreState::m_scoreState;

void RecordScoreState::Init()
{
	m_entityFactory.ResetIdCounter();
	CreateSystems();
	CreateUI();

	for (auto& system : m_systems)
	{
		system->Init(*this);
	}
}

void RecordScoreState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
	m_eventManager.RemoveAllEvents();
	m_systems.clear();
}

void RecordScoreState::HandleEvents(GameEngine & game)
{
	for (auto& event : m_eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::UIEvent)
		{
			continue;
		}

		UIEvent* uiEvent = static_cast<UIEvent*>(event.get());
		if (uiEvent->GetButtonName() == "back_button")
		{
			game.PopState();
		}
	}
	m_eventManager.RemoveReadEvents();
}

void RecordScoreState::Update(GameEngine & game, float deltaTime)
{
	for (auto& system : m_systems)
	{
		system->Update(deltaTime, *this);
	}
}

void RecordScoreState::CreateSystems()
{
	m_systems.push_back(std::make_unique<UIButtonSystem>());
}

void RecordScoreState::CreateUI()
{
	int score = Utilities::LoadRecordScore("record.txt");
	std::string text = "Best Score: " + std::to_string(score);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 50.0f, APP_VIRTUAL_HEIGHT - 200), text.c_str(), Color(0.0f, 0.8f, 0.8f)));
	Color color(1.0f, 1.0f, 1.0f);
	Color hoverColor(0.0f, 0.8f, 0.9f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIButton(Vector2D(APP_VIRTUAL_WIDTH / 2 - 50.0f, APP_VIRTUAL_HEIGHT - 400), 180.0f, 30.0f, "Back", color, hoverColor, "back_button"));
}