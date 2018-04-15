#pragma once

#include "Component.h"

class BallComponent : public Component
{
public:
	BallComponent(const Vector2D& startPosition);
	const Vector2D& GetStartPosition() const;
private:
	Vector2D m_startPosition;
};
