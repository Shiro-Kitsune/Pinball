#pragma once

#include "System.h"
class Entity;
class BoundingCircle2D;
class BoundingBox2D;
class Background;
class CLineSegment;
class FlipperComponent;

class CollisionSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	bool CheckForCollision(Entity& entity1, Entity& entity2);
	bool CircleCircleCollision(Entity& entity1, BoundingCircle2D& collider1, Entity& entity2, BoundingCircle2D& collider2);
	bool CircleBoxCollision(Entity& entity1, BoundingCircle2D& collider1, Entity& entity2, BoundingBox2D& collider2);
	void CircleBackgroundCollision(Entity& entity1, BoundingCircle2D& collider1, Background& background);
	bool CircleLineSegmentCollision(Entity& entity, BoundingCircle2D& collider, const CLineSegment& lineSegment);
	void CircleFlipperCollision(Entity& entity1, BoundingCircle2D& collider1, Entity& entity2, FlipperComponent& flipper);
	std::optional<Vector2D> LineLineIntersection(const Vector2D& line1Start, const Vector2D& line1End, const Vector2D& line2Start, const Vector2D& line2End);
	std::vector<CLineSegment*> CastRayToBackground(const Vector2D& origin, const Vector2D& direction, CTable& lines);
};
