#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(std::string text, Color color, bool visibility) : m_text(text), m_color(color), m_visible(visibility)
{
}

void TextComponent::SetText(std::string text)
{
	m_text = text;
}

const std::string & TextComponent::GetText() const
{
	return m_text;
}

Color TextComponent::GetColor() const
{
	return m_color;
}

void TextComponent::SetColor(Color color)
{
	m_color = color;
}

void TextComponent::SetVisibility(bool visible)
{
	m_visible = visible;
}

bool TextComponent::IsVisible() const
{
	return m_visible;
}
