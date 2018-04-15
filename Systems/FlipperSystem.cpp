#include "stdafx.h"
#include "FlipperSystem.h"
#include "FlipperComponent.h"
#include "EntityManager.h"
#include "GameState.h"
#include "Entity.h"
#include "Transform.h"

void FlipperSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();

	for (auto& entity : entityManager.GetEntities())
	{
		FlipperComponent* flipper = entity->GetComponent<FlipperComponent>();
		if (flipper == nullptr)
		{
			continue;
		}

		Transform* transform = entity->GetComponent<Transform>();
		float angle = transform->GetAngle();

		if (flipper->FlipAction())
		{
			if (flipper->GetFlipperSide() == FlipperComponent::FlipperSide::Left)
			{
				angle = (angle >= flipper->GetMaxAngle()) ? flipper->GetMaxAngle() : (angle + flipper->GetAngularVelocity() * (deltaTime * 0.001f));
			}
			else
			{
				angle = (angle <= -flipper->GetMaxAngle()) ? -flipper->GetMaxAngle() : (angle - flipper->GetAngularVelocity() * (deltaTime * 0.001f));
			}
		}
		else
		{
			if (flipper->GetFlipperSide() == FlipperComponent::FlipperSide::Left)
			{
				angle = (angle <= -flipper->GetMaxAngle()) ? -flipper->GetMaxAngle() : (angle - flipper->GetAngularVelocity() * (deltaTime * 0.001f));
			}
			else
			{
				angle = (angle >= flipper->GetMaxAngle()) ? flipper->GetMaxAngle() : (angle + flipper->GetAngularVelocity() * (deltaTime * 0.001f));
			}
			
		}
		transform->SetAngle(angle);
	}
}
