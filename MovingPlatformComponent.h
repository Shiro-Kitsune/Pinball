#pragma once

#include "Component.h"

class MovingPlatformComponent : public Component
{
public:
	MovingPlatformComponent(const Vector2D& startPosition, float maxDisplacement);
	float GetMaxDisplacement() const;
	const Vector2D& GetStartPosition() const;
private:
	Vector2D m_startPosition;
	float m_maxDisplacement;
};