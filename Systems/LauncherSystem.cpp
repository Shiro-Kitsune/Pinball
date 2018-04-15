#include "stdafx.h"
#include "LauncherSystem.h"
#include "../EntityManager.h"
#include "../Components/LauncherComponent.h"
#include "../States/GameState.h"
#include "../Entity.h"
#include "Transform.h"

void LauncherSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	for (auto& entity : entityManager.GetEntities())
	{
		LauncherComponent* launcher = entity->GetComponent<LauncherComponent>();
		if (launcher == nullptr)
		{
			continue;
		}

		Transform* transform = entity->GetComponent<Transform>();
		Vector2D position = transform->GetPosition();

		if (launcher->LaunchAction())
		{
			launcher->SetMoving(true);
			if (position.y > launcher->GetMinPositionY())
			{
				position.y -= launcher->GetVerticalSpeed() * (deltaTime * 0.001f);
				launcher->SetLastPositionY(position.y);
			}
		}
		else
		{
			//Return Launcher to its original position after key is released
			if (launcher->IsMoving())
			{
				if (position.y < launcher->GetMaxPositionY())
				{
					position.y += launcher->GetVerticalSpeed() * 3 * (deltaTime * 0.001f);
				}
				else
				{
					launcher->SetMoving(false);
					float displacement = launcher->GetMaxPositionY() - launcher->GetLastPositionY();
					eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::LaunchBall, displacement));
				}
			}
		}
		transform->SetPosition(position);
		break;
	}
}
