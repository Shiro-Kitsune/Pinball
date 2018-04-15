#pragma once

#include "System.h"
class RigidBody2D;
class Entity;
class Transform;
class BallComponent;
class EventManager;

class BallSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void HandleEvents(RigidBody2D& rigidBody, EventManager& eventManager);
	bool IsBallOffScreen(const Vector2D& position);
	void ResetBall(const BallComponent& ball, Transform& transform, RigidBody2D& rigidBody);
};