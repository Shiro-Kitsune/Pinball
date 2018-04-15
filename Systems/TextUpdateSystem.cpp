#include "stdafx.h"
#include "TextUpdateSystem.h"
#include "GameState.h"
#include "Entity.h"
#include "TextComponent.h"

void TextUpdateSystem::Init(GameState & gameState)
{
	std::shared_ptr<Entity> text = gameState.GetEntityManager().FindEntityByName("lives_text");
	if (text != nullptr)
	{
		m_livesText = text->GetComponent<TextComponent>();
		m_livesText->SetText("Lives: " + std::to_string(m_lives));
	}

	text = gameState.GetEntityManager().FindEntityByName("score_text");
	if (text != nullptr)
	{
		m_scoreText = text->GetComponent<TextComponent>();
		m_scoreText->SetText("Score: " + std::to_string(m_score));
	}
}

void TextUpdateSystem::Update(float deltaTime, GameState & gameState)
{
	for (auto& event : gameState.GetEventManager().GetEvents())
	{
		if (event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}

		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
		if (gameEvent->GetGameEventType() == GameEventType::ScoreChanged)
		{
			gameEvent->MarkAsRead();
			m_score += gameEvent->GetValue();
			UpdateScoreText();
		}
		else if (gameEvent->GetGameEventType() == GameEventType::LivesDecreased)
		{
			gameEvent->MarkAsRead();
			m_lives += gameEvent->GetValue();
			UpdateLivesText();

			if (m_lives <= 0)
			{
				EventManager& eventManager = gameState.GetEventManager();
				eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerDied, m_score));
			}
		}
	}
}

void TextUpdateSystem::UpdateScoreText()
{
	if (m_scoreText != nullptr)
	{
		m_scoreText->SetText("Score: " + std::to_string(m_score));
	}
}

void TextUpdateSystem::UpdateLivesText()
{
	if (m_livesText != nullptr)
	{
		m_livesText->SetText("Lives: " + std::to_string(m_lives));
	}
}
