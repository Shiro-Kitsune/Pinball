#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GameState.h"
#include "RigidBody2D.h"
#include "Transform.h"

const Vector2D PhysicsSystem::GRAVITY(0.0f, -80.9f);

void PhysicsSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		RigidBody2D* rigidBody = entity->GetComponent<RigidBody2D>();
		if (rigidBody == nullptr)
		{
			continue;
		}

		Transform* transform = entity->GetComponent<Transform>();
		if (transform != nullptr)
		{
			UpdateEntity(deltaTime, *transform, *rigidBody);
		}
	}
}

void PhysicsSystem::UpdateEntity(float deltaTime, Transform& transform, RigidBody2D& rigidBody)
{
	Vector2D position = transform.GetPosition();
	float angle = transform.GetAngle();
	Vector2D velocity = rigidBody.GetVelocity();
	float angularVelocity = rigidBody.GetAngularVelocity();
	float deltaTimeInSeconds = deltaTime * 0.001f;

	transform.SetPrevPosition(position);

	//Kinematic objects are not affected by forces including gravity
	if (!rigidBody.IsKinematic())
	{
		if (!rigidBody.IsGrounded())
		{
			rigidBody.ApplyForce(GRAVITY);
		}
		Vector2D acceleration = rigidBody.GetAcceleration();
		velocity += acceleration * deltaTimeInSeconds;
	}
	position += velocity * deltaTimeInSeconds;
	angle += angularVelocity * deltaTimeInSeconds;

	rigidBody.SetAcceleration(Vector2D(0.0f, 0.0f)); //Reset acceleration because the force is applied every frame and we do not acceleration to go to infinity
	rigidBody.SetVelocity(velocity);
	transform.SetPosition(position);
	transform.SetAngle(angle);
}
