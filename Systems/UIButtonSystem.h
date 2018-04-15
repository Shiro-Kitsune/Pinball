#pragma once

#include "System.h"
class BoundingBox2D;
class Entity;
class Transform;

class UIButtonSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	bool IsMouseOverButton(const Transform& transform, const BoundingBox2D& boundingBox);
	bool IsPointInTriangle(const Vector2D& mousePoint, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3);
	float Sign(const Vector2D& mousePoint, const Vector2D& p1, const Vector2D& p2);
	void ChangeButtonColor(Entity& entity, const Color& color);
};
