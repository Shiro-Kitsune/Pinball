#pragma once

#include "../Systems/Renderer.h"
#include "../EntityManager.h"
#include "../EntityFactory.h"
#include "../EventManager.h"

class GameEngine;

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void HandleEvents(GameEngine& game) = 0;
	virtual void Update(GameEngine& game, float deltaTime) = 0;
	virtual void Render();

	virtual EventManager& GetEventManager() final;
	virtual EntityManager& GetEntityManager() final;
	virtual EntityFactory& GetEntityFactory() final;
protected:
	GameState() { }
protected:
	EntityManager m_entityManager;
	EventManager m_eventManager;
	EntityFactory m_entityFactory;
	Renderer m_renderingSystem;	
};
