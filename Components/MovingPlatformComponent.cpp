#include "stdafx.h"
#include "MovingPlatformComponent.h"

MovingPlatformComponent::MovingPlatformComponent(const Vector2D & startPosition, float maxDisplacement) : m_startPosition(startPosition), m_maxDisplacement(maxDisplacement)
{
}

float MovingPlatformComponent::GetMaxDisplacement() const
{
	return m_maxDisplacement;
}

const Vector2D & MovingPlatformComponent::GetStartPosition() const
{
	return m_startPosition;
}
