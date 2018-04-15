#include "stdafx.h"
#include "PlayGameState.h"
#include "StartMenuState.h"
#include "PauseGameState.h"
#include "GameEngine.h"
#include "PhysicsSystem.h"
#include "TargetSystem.h"
#include "CollisionSystem.h"
#include "BallSystem.h"
#include "Entity.h"
#include "FlipperSystem.h"
#include "FlipperComponent.h"
#include "LauncherSystem.h"
#include "TargetComponent.h"
#include "CollisionRemovalSystem.h"
#include "TextUpdateSystem.h"
#include "MovingPlatformSystem.h"

PlayGameState PlayGameState::m_playGameState;

void PlayGameState::Init()
{
	m_entityFactory.ResetIdCounter();
	m_gameOver = false;

	CreateSystems();
	CreateMainGameUI();
	CreateObjects();
	CreateField();

	for (auto& system : m_systems)
	{
		system->Init(*this);
	}
}

void PlayGameState::Cleanup()
{
	m_systems.clear();
	m_entityManager.RemoveAllEntities();
	m_eventManager.RemoveAllEvents();
}

void PlayGameState::HandleEvents(GameEngine & game)
{
	m_eventManager.RemoveReadEvents();

	for (auto& event : m_eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}
		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
		switch (gameEvent->GetGameEventType())
		{
		    case GameEventType::PlayerDied:
			{
				gameEvent->MarkAsRead();
				m_systems.clear();
				m_entityManager.RemoveAllEntities();
				m_gameOver = true;
				CreateEndGameUI(gameEvent->GetValue());
				//Save record score
				int previousScore = Utilities::LoadRecordScore("record.txt");
				if (previousScore < gameEvent->GetValue())
				{
					Utilities::SaveRecordScore("record.txt", gameEvent->GetValue());
				}
				break;
			}
		}
	}

	if (m_gameOver)
	{
		if (App::IsKeyPressed(VK_RETURN))
		{
			game.ChangeState(StartMenuState::Instance());
		}
	}
	else
	{
		if (App::IsKeyPressed('P'))
		{
			game.PushState(PauseGameState::Instance());
		}
	}
}

void PlayGameState::Update(GameEngine& game, const float deltaTime)
{
	for (auto& system : m_systems)
	{
		system->Update(deltaTime, *this);
	}
}

void PlayGameState::CreateObjects()
{
	m_entityManager.AddEntity(m_entityFactory.CreateBall(Vector2D(954, 125)));
	m_entityManager.AddEntity(m_entityFactory.CreateFlipper(Vector2D(380.0f, 130.0f), FlipperComponent::FlipperSide::Left));
	m_entityManager.AddEntity(m_entityFactory.CreateFlipper(Vector2D(635.0f, 130.0f), FlipperComponent::FlipperSide::Right));
	m_entityManager.AddEntity(m_entityFactory.CreateLauncher(Vector2D(954.0f, 53.0f), VK_SPACE));
	m_entityManager.AddEntity(m_entityFactory.CreateTarget(Vector2D(400.0f, 500.0f), TargetType::Small));
	m_entityManager.AddEntity(m_entityFactory.CreateTarget(Vector2D(600.0f, 500.0f), TargetType::Medium));
	m_entityManager.AddEntity(m_entityFactory.CreateTarget(Vector2D(500.0f, 570.0f), TargetType::Large));
	m_entityManager.AddEntity(m_entityFactory.CreateStaticPlatform(Vector2D(800.0f, 460.0f), 40, 150));
	m_entityManager.AddEntity(m_entityFactory.CreateStaticPlatform(Vector2D(250.0f, 540.0f), 50, 170));
	m_entityManager.AddEntity(m_entityFactory.CreateStaticPlatform(Vector2D(250.0f, 540.0f), 150, 30));
	m_entityManager.AddEntity(m_entityFactory.CreateMovingPlatform(Vector2D(500.0f, 300.0f), 100, 30));
}

void PlayGameState::CreateField()
{
	m_entityManager.AddEntity(m_entityFactory.CreateBackground("table.txt"));
}

void PlayGameState::CreateSystems()
{
	m_systems.push_back(std::make_unique<PhysicsSystem>());
	m_systems.push_back(std::make_unique<CollisionSystem>());
	m_systems.push_back(std::make_unique<FlipperSystem>());
	m_systems.push_back(std::make_unique<LauncherSystem>());
	m_systems.push_back(std::make_unique<BallSystem>());
	m_systems.push_back(std::make_unique<MovingPlatformSystem>());
	m_systems.push_back(std::make_unique<TargetSystem>());
	m_systems.push_back(std::make_unique<TextUpdateSystem>());
	m_systems.push_back(std::make_unique<CollisionRemovalSystem>());
}

void PlayGameState::CreateMainGameUI()
{
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH - 100.0f, APP_VIRTUAL_HEIGHT - 25.0f), "Lives: ", Color(1.0f, 1.0f, 1.0f), "lives_text"));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(10.0f, APP_VIRTUAL_HEIGHT - 25.0f), "Score: ", Color(1.0f, 1.0f, 1.0f), "score_text"));
}

void PlayGameState::CreateEndGameUI(int score)
{
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(430, APP_VIRTUAL_HEIGHT - 180), "GAME OVER", Color(0.7f, 0.0f, 0.0f)));
	std::string scoreString = "Score: " + std::to_string(score);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(430, APP_VIRTUAL_HEIGHT - 220), scoreString.c_str(), Color(1.0f, 1.0f, 1.0f)));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(412, APP_VIRTUAL_HEIGHT - 400), "Press Enter to return to Main menu", Color(0.855f, 0.647f, 0.125f)));
}