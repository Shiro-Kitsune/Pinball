#pragma once

#include "Component.h"

class RenderingComponent : public Component
{
public:
	RenderingComponent(const Color& color, bool visible = true);
	RenderingComponent(const Color& color, std::vector<Vector2D> points, bool visible = true);

	void AddPoint(const Vector2D& point);
	void DeleteGeometry();
	const std::vector<Vector2D>& GetGeometry() const;
	const Color& GetColor() const;
	void SetColor(const Color& color);
	void SetVisibility(bool visible);
	bool IsVisible() const;
private:
	Color m_color;
	bool m_visible;
	std::vector<Vector2D> m_points;
};
