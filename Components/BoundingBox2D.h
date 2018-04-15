#pragma once

#include "Component.h"

class BoundingBox2D : public Component
{
public:
	BoundingBox2D(float width, float height);
	float GetWidth() const;
	float GetHeight() const;
	float GetHalfWidth() const;
	float GetHalfHeight() const;
	void SetWidth(float width);
	void SetHeight(float height);
private:
	float m_width;
	float m_height;
	float m_halfWidth;
	float m_halfHeight;
};
