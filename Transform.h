#pragma once

#include "Component.h"

class Transform : public Component
{
public:
	Transform(const Vector2D& position = Vector2D(0.0f, 0.0f), float angle = 0.0f);

	const Vector2D& GetPosition() const;
	void SetPosition(const Vector2D& position);
	const Vector2D& GetPrevPosition() const;
	void SetPrevPosition(const Vector2D& position);
	float GetAngle() const;
	void SetAngle(float angle);
private:
	Vector2D m_position;
	float m_angle;
	Vector2D m_prevPosition;
};