#pragma once

#include "Component.h"

class FlipperComponent : public Component
{
public:
	enum class FlipperSide { Left, Right };

	FlipperComponent(int flipKeyCode, float angularVelocity, float maxAngle, FlipperComponent::FlipperSide flipperSide);
	float GetAngularVelocity() const;
	bool FlipAction() const;
	float GetMaxAngle() const;
	FlipperComponent::FlipperSide GetFlipperSide() const;
private:
	int m_flipKeyCode;
	float m_angularVelocity;
	float m_maxAngle;
	FlipperComponent::FlipperSide m_flipperSide;
};
