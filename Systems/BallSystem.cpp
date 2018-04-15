#include "stdafx.h"
#include "BallSystem.h"
#include "../EntityManager.h"
#include "../Entity.h"
#include "../States/GameState.h"
#include "BallComponent.h"
#include "Transform.h"
#include "../Events/Event.h"
#include "../Components/RigidBody2D.h"

void BallSystem::Update(float deltaTime, GameState& gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	for (auto& entity : entityManager.GetEntities())
	{
		BallComponent* ball = entity->GetComponent<BallComponent>();
		if (ball == nullptr)
		{
			continue;
		}

		RigidBody2D* rigidBody = entity->GetComponent<RigidBody2D>();
		HandleEvents(*rigidBody, eventManager);

		Transform* transform = entity->GetComponent<Transform>();
		if (IsBallOffScreen(transform->GetPosition()))
		{
			gameState.GetEventManager().AddEvent(std::make_unique<GameEvent>(GameEventType::LivesDecreased, -1));
			ResetBall(*ball, *transform, *rigidBody);
		}
	}
}

void BallSystem::HandleEvents(RigidBody2D& rigidBody, EventManager & eventManager)
{
	for (auto& event : eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}

		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
		if (gameEvent->GetGameEventType() == GameEventType::LaunchBall)
		{
			gameEvent->MarkAsRead();
			if (rigidBody.IsGrounded())
			{
				float displacement = gameEvent->GetValue();
				Vector2D force(0.00f, 599.0f * displacement);
				rigidBody.ApplyForce(force);
				rigidBody.SetGrounded(false);
			}
		}
	}
}

bool BallSystem::IsBallOffScreen(const Vector2D& position)
{
	bool yOutOfBounds = (position.y < -10.0f) || (position.y > APP_VIRTUAL_HEIGHT + 10.0f);
	bool xOutOfBounds = (position.x < -10.0f) || (position.x > APP_VIRTUAL_WIDTH + 10.0f);
	return yOutOfBounds || xOutOfBounds;
}

void BallSystem::ResetBall(const BallComponent& ball, Transform& transform, RigidBody2D& rigidBody)
{
	rigidBody.SetVelocity(Vector2D());
	rigidBody.SetAcceleration(Vector2D());
	rigidBody.SetGrounded(true);
	transform.SetPosition(ball.GetStartPosition());
	transform.SetAngle(0.0f);
}
