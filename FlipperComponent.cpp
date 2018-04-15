#include "stdafx.h"
#include "FlipperComponent.h"

FlipperComponent::FlipperComponent(int flipKeyCode, float angularVelocity, float maxAngle, FlipperComponent::FlipperSide flipperSide) : m_flipKeyCode(flipKeyCode), m_angularVelocity(angularVelocity), m_maxAngle(maxAngle)
{
	m_flipperSide = flipperSide;
}

float FlipperComponent::GetAngularVelocity() const
{
	return m_angularVelocity;
}

bool FlipperComponent::FlipAction() const
{
	return App::IsKeyPressed(m_flipKeyCode);;
}

float FlipperComponent::GetMaxAngle() const
{
	return m_maxAngle;
}

FlipperComponent::FlipperSide FlipperComponent::GetFlipperSide() const
{
	return m_flipperSide;
}