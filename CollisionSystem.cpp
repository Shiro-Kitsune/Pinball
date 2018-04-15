#include "stdafx.h"
#include "CollisionSystem.h"
#include "GameState.h"
#include "EntityManager.h"
#include "BoundingBox2D.h"
#include "BoundingCircle2D.h"
#include "Entity.h"
#include "Transform.h"
#include "BallComponent.h"
#include "Collision.h"
#include "Background.h"
#include "RigidBody2D.h"
#include "FlipperComponent.h"
#include "RenderingComponent.h"
#include "BallComponent.h"

void CollisionSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		BallComponent* ball = entity->GetComponent<BallComponent>();
		if (ball == nullptr)
		{
			continue;
		}

		RigidBody2D* ballRigidBody = entity->GetComponent<RigidBody2D>();
		if (!ballRigidBody->IsGrounded())
		{
			for (auto& entity2 : manager.GetEntities())
			{
				if (entity->GetId() == entity2->GetId())
				{
					continue;
				}


				bool collisionHappened = CheckForCollision(*entity, *entity2);
				if (collisionHappened)
				{
					entity->AddCollision(Collision(entity2));
					entity2->AddCollision(Collision(entity));
				}
			}
		}
	}
}

bool CollisionSystem::CheckForCollision(Entity& ball, Entity& entity2)
{
	BoundingCircle2D* ballCollider = ball.GetComponent<BoundingCircle2D>();
	if(ballCollider == nullptr)
	{
		return false;
	}

	BoundingCircle2D* circleCollider2 = entity2.GetComponent<BoundingCircle2D>();
	BoundingBox2D* boxCollider2 = entity2.GetComponent<BoundingBox2D>();
	Background* background = entity2.GetComponent<Background>();
	FlipperComponent* flipper = entity2.GetComponent<FlipperComponent>();

	bool collision = false;
	if (circleCollider2 != nullptr)
	{
		collision = CircleCircleCollision(ball, *ballCollider, entity2, *circleCollider2);
	}
	else if (boxCollider2 != nullptr)
	{
		collision = CircleBoxCollision(ball, *ballCollider, entity2, *boxCollider2);
	}
	else if (background != nullptr)
	{
		CircleBackgroundCollision(ball, *ballCollider, *background);
	}
	else if (flipper != nullptr)
	{
		CircleFlipperCollision(ball, *ballCollider, entity2, *flipper);
	}
	return collision;
}

bool CollisionSystem::CircleCircleCollision(Entity& entity1, BoundingCircle2D& collider1, Entity& entity2, BoundingCircle2D& collider2)
{
	Transform* transform1 = entity1.GetComponent<Transform>();
	Transform* transform2 = entity2.GetComponent<Transform>();
	Vector2D position1 = transform1->GetPosition();
	Vector2D position2 = transform2->GetPosition();
	float radius1 = collider1.GetRadius();
	float radius2 = collider2.GetRadius();
	return Utilities::CircleOverlap(position1, radius1, position2, radius2);
}

bool CollisionSystem::CircleBoxCollision(Entity& entity1, BoundingCircle2D& collider1, Entity& entity2, BoundingBox2D& collider2)
{
	Vector2D ballPosition = entity1.GetComponent<Transform>()->GetPosition();
	float ballRadius = collider1.GetRadius();
	Vector2D boxPosition = entity2.GetComponent<Transform>()->GetPosition();
	float halfWidth = collider2.GetHalfWidth();
	float halfHeight = collider2.GetHalfHeight();
	Vector2D boxBottomPoint(boxPosition.x - halfWidth, boxPosition.y - halfHeight);
	Vector2D boxTopPoint(boxPosition.x + halfWidth, boxPosition.y + halfHeight);

	float nearestX = max(boxBottomPoint.x, min(ballPosition.x, boxTopPoint.x));
	float nearestY = max(boxBottomPoint.y, min(ballPosition.y, boxTopPoint.y));
	float deltaX = ballPosition.x - nearestX;
	float deltaY = ballPosition.y - nearestY;

	if ((deltaX * deltaX + deltaY * deltaY) > (ballRadius * ballRadius))
	{
 		return false;
	}

	Vector2D dist = Vector2D(ballPosition.x - nearestX, ballPosition.y - nearestY);
	RigidBody2D* ballRigidBody = entity1.GetComponent<RigidBody2D>();
	Vector2D ballVelocity = ballRigidBody->GetVelocity();

	//If ball is moving toward the box, update ball velocity
	if (ballVelocity.DotProduct(dist) < 0.05)
	{
		Vector2D normal(-dist.y, dist.x);
		float normalAngle = Vector2D(normal.y, normal.x).Heading();
		float incomingAngle = Vector2D(ballVelocity.y, ballVelocity.x).Heading();
		float theta = normalAngle - incomingAngle;
		ballVelocity.Rotate(-2 * theta);
		ballRigidBody->SetVelocity(ballVelocity);
	}
	return true;
}

void CollisionSystem::CircleBackgroundCollision(Entity& entity1, BoundingCircle2D& collider1, Background& background)
{
	Vector2D velocityDirection = entity1.GetComponent<RigidBody2D>()->GetVelocity();
	velocityDirection.Normalize();
	std::vector<CLineSegment*> linesOnTheWay = CastRayToBackground(entity1.GetComponent<Transform>()->GetPosition(), velocityDirection, background.GetTable());

	bool collision = false;
	for (auto& line : linesOnTheWay)
	{
		collision = CircleLineSegmentCollision(entity1, collider1, *line);
		if (collision)
		{
			break;
		}
	}
}

bool CollisionSystem::CircleLineSegmentCollision(Entity & entity, BoundingCircle2D & collider, const CLineSegment & lineSegment)
{
	RigidBody2D* ballRigidBody = entity.GetComponent<RigidBody2D>();
	Transform* ballTransform = entity.GetComponent<Transform>();

	Vector2D ballPosition = ballTransform->GetPosition();
	Vector2D ballOldPosition = ballTransform->GetPrevPosition();
	Vector2D lineStartPoint(lineSegment.m_start.m_x, lineSegment.m_start.m_y);
	Vector2D lineEndPoint(lineSegment.m_end.m_x, lineSegment.m_end.m_y);

	Vector2D segmentVector = lineEndPoint - lineStartPoint;
	Vector2D ballSegmentDist = ballPosition - lineStartPoint;
	Vector2D normalizedSegmentVector = segmentVector.GetNormalized();
	float projectionLength = ballSegmentDist.DotProduct(normalizedSegmentVector);

	Vector2D closestPoint;
	if (projectionLength < 0)
	{
		closestPoint = lineStartPoint;
	}
	else if (projectionLength * projectionLength > segmentVector.MagnitudeSquared())
	{
		closestPoint = lineEndPoint;
	}
	else
	{
		Vector2D projectionVector = normalizedSegmentVector * projectionLength;
		closestPoint = lineStartPoint + projectionVector;
	}

	Vector2D distanceVector = ballPosition - closestPoint;
	float ballRadius = collider.GetRadius();

	//There is no collision in current position, check collisions in past
	if (distanceVector.MagnitudeSquared() > (ballRadius * ballRadius))
	{
		if ((ballPosition.x != ballOldPosition.x) || (ballPosition.y != ballOldPosition.y))
		{
			//Cast "ray" from current ball position to the old position to check if there were any intersections between frames
			std::optional<Vector2D> intersection = LineLineIntersection(ballPosition, ballOldPosition, lineStartPoint, lineEndPoint);

			//No intersection
			if (!intersection.has_value())
			{
				return false;
			}

			Vector2D intersectionPoint = intersection.value();
			float distanceFromIntersection = ballPosition.Distance(intersectionPoint);
			float distToMoveBack = distanceFromIntersection + ballRadius;
			ballTransform->SetPosition(ballPosition - distToMoveBack); //Move ball back to actual collision point
		}
	}

	//Must stop if collision is with ground type line
	if (lineSegment.m_type == 2)
	{
		ballRigidBody->SetGrounded(true);
		ballRigidBody->SetVelocity(Vector2D(0.0f, 0.0f));
		Vector2D ballStartPosition = entity.GetComponent<BallComponent>()->GetStartPosition();
		ballTransform->SetPosition(ballStartPosition);
	}
	else
	{
		//Calculate reflected velocity
		Vector2D normal((lineEndPoint.y - lineStartPoint.y), -(lineEndPoint.x - lineStartPoint.x));
		normal.Normalize();
		Vector2D ballVelocity = ballRigidBody->GetVelocity();
		ballVelocity = normal * (-2 * ballVelocity.DotProduct(normal)) + ballVelocity;
		ballVelocity.Limit(400);
		ballRigidBody->SetVelocity(ballVelocity);
	}

	return true;
}

void CollisionSystem::CircleFlipperCollision(Entity& entity1, BoundingCircle2D& collider, Entity& entity2, FlipperComponent& flipper)
{
	RigidBody2D* ballRigidBody = entity1.GetComponent<RigidBody2D>();
	Transform* ballTransform = entity1.GetComponent<Transform>();
	Vector2D ballPosition = ballTransform->GetPosition();

	RenderingComponent* flipperGeometry = entity2.GetComponent<RenderingComponent>();
	Vector2D flipperStartPoint = flipperGeometry->GetGeometry()[0];
	Vector2D flipperEndPoint = flipperGeometry->GetGeometry()[1];
	Transform* flipperTransform = entity2.GetComponent<Transform>();
	float flipperAngle = Utilities::ToRadians(flipperTransform->GetAngle());
	flipperStartPoint.Rotate(flipperAngle);
	flipperEndPoint.Rotate(flipperAngle);
	flipperStartPoint += flipperTransform->GetPosition();
	flipperEndPoint += flipperTransform->GetPosition();

	Vector2D segmentVector = flipperEndPoint - flipperStartPoint;
	Vector2D ballStartPointDist = ballPosition - flipperStartPoint;
	Vector2D normalizedSegmentVector = segmentVector.GetNormalized();
	float projectionLength = ballStartPointDist.DotProduct(normalizedSegmentVector);

	Vector2D closestPoint;
	if (projectionLength < 0)
	{
		closestPoint = flipperStartPoint;
	}
	else if (projectionLength * projectionLength > segmentVector.MagnitudeSquared())
	{
		closestPoint = flipperEndPoint;
	}
	else
	{
		Vector2D projectionVector = normalizedSegmentVector * projectionLength;
		closestPoint = flipperStartPoint + projectionVector;
	}

	Vector2D distanceVector = ballPosition - closestPoint;
	float ballRadius = collider.GetRadius();
	//There is no collision
	if (distanceVector.MagnitudeSquared() > (ballRadius * ballRadius))
	{
		return;
	}

	Vector2D normal(-(flipperEndPoint.y - flipperStartPoint.y), (flipperEndPoint.x - flipperStartPoint.x));
	normal.Normalize();
	Vector2D ballVelocity = ballRigidBody->GetVelocity();
	ballVelocity = normal * (-2 * ballVelocity.DotProduct(normal)) + ballVelocity;
	ballVelocity *= 1.2;
	ballVelocity.Limit(400);
	ballRigidBody->SetVelocity(ballVelocity);
}

std::vector<CLineSegment*> CollisionSystem::CastRayToBackground(const Vector2D& rayOrigin, const Vector2D& direction, CTable& table)
{
	std::vector<CLineSegment*> intersectedLines;
	Vector2D rayEnd = direction * 1500.0f;

	for (auto& line : table.m_lines)
	{
		Vector2D lineStartPoint(line.m_start.m_x, line.m_start.m_y);
		Vector2D lineEndPoint(line.m_end.m_x, line.m_end.m_y);
		std::optional<Vector2D> intersection = LineLineIntersection(rayOrigin, rayEnd, lineStartPoint, lineEndPoint);
		if (intersection.has_value())
		{
			intersectedLines.push_back(&line);
		}
	}
	return intersectedLines;
}

std::optional<Vector2D> CollisionSystem::LineLineIntersection(const Vector2D & line1Start, const Vector2D & line1End, const Vector2D & line2Start, const Vector2D & line2End)
{
	double denominator = (line2End.y - line2Start.y) * (line1End.x - line2Start.x) - (line2End.x - line2Start.x) * (line1End.y - line1Start.y);
	double uA = ((line2End.x - line2Start.x) * (line1Start.y - line2Start.y) - (line2End.y - line2Start.y) * (line1Start.x - line2Start.x)) / denominator;
	double uB = ((line1End.x - line1Start.x) * (line1Start.y - line2Start.y) - (line1End.y - line1Start.y) * (line1Start.x - line2Start.x)) / denominator;

	//If uA and uB are between 0 and 1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		//Intersection point
		float intersectionX = static_cast<float>(line1Start.x + (uA * (line1End.x - line1Start.x)));
		float intersectionY = static_cast<float>(line1Start.y + (uA * (line1End.y - line1Start.y)));
		return std::optional<Vector2D>{Vector2D(intersectionX, intersectionY)};
	}
	return std::nullopt;
}