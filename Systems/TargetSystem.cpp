#include "stdafx.h"
#include "TargetSystem.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "GameState.h"
#include "Entity.h"
#include "TargetComponent.h"
#include "BallComponent.h"
#include "RenderingComponent.h"

void TargetSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	for (auto& entity : entityManager.GetEntities())
	{
		TargetComponent* target = entity->GetComponent<TargetComponent>();
		if (target == nullptr)
		{
			continue;
		}

		if (target->WasHit())
		{
			if (target->ReadyToChangeColor())
			{
				ChangeTargetColorToStandard(*entity, *target);
			}
			target->IncreaseTimeElapsedSinceColorChange(deltaTime);
		}

		for (auto collision : entity->GetCollisions())
		{
			BallComponent* ball = collision.GetCollidedEntity()->GetComponent<BallComponent>();
			if (ball == nullptr)
			{
				continue;
			}

			ChangeTargetColorToAlternative(*entity, *target);
			gameState.GetEventManager().AddEvent(std::make_unique<GameEvent>(GameEventType::ScoreChanged, target->GetValue()));
			break;
		}
	}
}

void TargetSystem::ChangeTargetColorToAlternative(Entity& entity, TargetComponent& target)
{
	RenderingComponent* renderingComponent = entity.GetComponent<RenderingComponent>();
	renderingComponent->SetColor(target.GetAlternateColor());
	target.ResetTimeElapsedSinceColorChange();
	target.SetWasHit(true);
}

void TargetSystem::ChangeTargetColorToStandard(Entity & entity, TargetComponent & target)
{
	RenderingComponent* renderingComponent = entity.GetComponent<RenderingComponent>();
	renderingComponent->SetColor(target.GetStandardColor());
	target.SetWasHit(false);
}
