#pragma once

#include "Component.h"

class BoundingCircle2D : public Component
{
public:
	BoundingCircle2D(float radius);
	float GetRadius() const;
	void SetRadius(float radius);
private:
	float m_radius;
};