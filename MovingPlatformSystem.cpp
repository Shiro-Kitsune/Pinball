#include "stdafx.h"
#include "MovingPlatformSystem.h"
#include "EntityManager.h"
#include "GameState.h"
#include "Entity.h"
#include "MovingPlatformComponent.h"
#include "RigidBody2D.h"
#include "Transform.h"

void MovingPlatformSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();

	for (auto& entity : entityManager.GetEntities())
	{
		MovingPlatformComponent* platform = entity->GetComponent<MovingPlatformComponent>();
		if (platform == nullptr)
		{
			continue;
		}

		Transform* transform = entity->GetComponent<Transform>();
		Vector2D position = transform->GetPosition();
		float maxDisplacement = platform->GetMaxDisplacement();

		if (position.DistanceSquared(platform->GetStartPosition()) > (maxDisplacement * maxDisplacement))
		{
			RigidBody2D* rigidBody = entity->GetComponent<RigidBody2D>();
			Vector2D velocity = rigidBody->GetVelocity();
			velocity *= -1.0f;
			rigidBody->SetVelocity(velocity);
		}
	}
}