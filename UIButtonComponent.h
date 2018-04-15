#pragma once

#include "Component.h"

class UIButtonComponent : public Component
{
public:
	UIButtonComponent(Color color, Color hoverColor);
	Color GetColor() const;
	Color GetHoverColor() const;
	void SetColor(Color color);
	void SetHoverColor(Color color);

private:
	Color m_color;
	Color m_hoverColor;
};