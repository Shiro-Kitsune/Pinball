#pragma once

#include "Component.h"

class TextComponent : public Component
{
public:
	TextComponent(std::string text, Color color = Color(1.0f, 1.0f, 1.0f), bool visible = true);

	void SetText(std::string text);
	const std::string& GetText() const;
	Color GetColor() const;
	void SetColor(Color color);
	void SetVisibility(bool visible);
	bool IsVisible() const;
private:
	std::string m_text;
	Color m_color;
	bool m_visible;
};
