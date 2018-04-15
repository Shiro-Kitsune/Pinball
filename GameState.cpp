#include "stdafx.h"
#include "GameState.h"

void GameState::Render()
{
	m_renderingSystem.Render(m_entityManager);
}

EventManager & GameState::GetEventManager()
{
	return m_eventManager;
}

EntityManager& GameState::GetEntityManager()
{
	return m_entityManager;
}

EntityFactory& GameState::GetEntityFactory()
{
	return m_entityFactory;
}