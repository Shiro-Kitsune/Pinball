#pragma once

#include "System.h"
class RigidBody2D;
class Entity;
class Transform;

class PhysicsSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void UpdateEntity(float deltaTime, Transform& transform, RigidBody2D& rigidBody);
private:
	static const Vector2D GRAVITY;
};
