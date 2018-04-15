#include "stdafx.h"
#include "UIButtonComponent.h"

UIButtonComponent::UIButtonComponent(Color color, Color hoverColor) : m_color(color), m_hoverColor(hoverColor)
{
}

Color UIButtonComponent::GetColor() const
{
	return m_color;
}

Color UIButtonComponent::GetHoverColor() const
{
	return m_hoverColor;
}

void UIButtonComponent::SetColor(Color color)
{
	m_color = color;
}

void UIButtonComponent::SetHoverColor(Color color)
{
	m_hoverColor = color;
}
