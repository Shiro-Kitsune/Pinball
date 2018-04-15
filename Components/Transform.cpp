#include "stdafx.h"
#include "Transform.h"

Transform::Transform(const Vector2D & position, float angle) : m_position(position), m_angle(angle), m_prevPosition(position)
{
}

const Vector2D & Transform::GetPosition() const
{
	return m_position;
}

float Transform::GetAngle() const
{
	return m_angle;
}

void Transform::SetPosition(const Vector2D & position)
{
	m_position = position;
}

const Vector2D & Transform::GetPrevPosition() const
{
	return m_prevPosition;
}

void Transform::SetPrevPosition(const Vector2D & position)
{
	m_prevPosition = position;
}

void Transform::SetAngle(float angle)
{
	m_angle = angle;
}
