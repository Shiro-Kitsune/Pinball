#include "stdafx.h"
#include "BallComponent.h"

BallComponent::BallComponent(const Vector2D & startPosition) : m_startPosition(startPosition)
{
}

const Vector2D & BallComponent::GetStartPosition() const
{
	return m_startPosition;
}