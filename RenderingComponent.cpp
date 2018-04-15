#include "stdafx.h"
#include "RenderingComponent.h"

RenderingComponent::RenderingComponent(const Color & color, bool visible) : m_color(color), m_visible(visible)
{
}

RenderingComponent::RenderingComponent(const Color & color, std::vector<Vector2D> points, bool visible) : m_color(color), m_points(std::move(points)), m_visible(visible)
{
}

void RenderingComponent::AddPoint(const Vector2D & point)
{
	m_points.push_back(point);
}

void RenderingComponent::DeleteGeometry()
{
	m_points.clear();
}

const std::vector<Vector2D>& RenderingComponent::GetGeometry() const
{
	return m_points;
}

const Color& RenderingComponent::GetColor() const
{
	return m_color;
}

void RenderingComponent::SetColor(const Color& color)
{
	m_color = color;
}

void RenderingComponent::SetVisibility(bool visible)
{
	m_visible = visible;
}

bool RenderingComponent::IsVisible() const
{
	return m_visible;
}