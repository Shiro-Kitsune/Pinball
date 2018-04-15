#include "stdafx.h"
#include "IntroGameState.h"
#include "../GameEngine.h"
#include "PlayGameState.h"
#include "../Entity.h"

IntroGameState IntroGameState::m_introState;

void IntroGameState::Init()
{
	m_entityFactory.ResetIdCounter();
	CreateMainGameUI();
}

void IntroGameState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
}

void IntroGameState::HandleEvents(GameEngine & game)
{
	if (App::IsKeyPressed(VK_RETURN))
	{
		game.ChangeState(PlayGameState::Instance());
	}
}

void IntroGameState::Update(GameEngine& game, float deltaTime)
{
}

void IntroGameState::CreateMainGameUI()
{
	Color color(0.8f, 0.8f, 0.8f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 30.0f, APP_VIRTUAL_HEIGHT - 60), "CONTROLS", Color(0.0f, 0.8f, 0.8f)));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(350, APP_VIRTUAL_HEIGHT - 200), "Space = launch ball", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(350, APP_VIRTUAL_HEIGHT - 250), "Right and left arrows = raise right or left flipper", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(350, APP_VIRTUAL_HEIGHT - 300), "P = pause game", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(412, APP_VIRTUAL_HEIGHT - 400), "Press Enter to start a game", Color(0.855f, 0.647f, 0.125f)));
}
