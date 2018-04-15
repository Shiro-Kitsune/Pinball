#include "stdafx.h"
#include "CollisionRemovalSystem.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"

void CollisionRemovalSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		entity->RemoveAllCollisions();
	}
}