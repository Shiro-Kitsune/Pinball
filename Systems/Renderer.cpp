#include "stdafx.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "Entity.h"
#include "RenderingComponent.h"
#include "TextComponent.h"
#include "Transform.h"
#include "Background.h"

void Renderer::Render(const EntityManager& entityManager) const
{
	for (auto& entity : entityManager.GetEntities())
	{
		Transform* transform = entity->GetComponent<Transform>();
		if (transform == nullptr)
		{
			Background* background = entity->GetComponent<Background>();
			if (background != nullptr)
			{
				RenderBackground(*background);
			}
			continue;
		}
		Vector2D position = transform->GetPosition();
		float angle = transform->GetAngle();

		RenderingComponent* renderingComponent = entity->GetComponent<RenderingComponent>();
		if (renderingComponent != nullptr && renderingComponent->IsVisible())
		{
			RenderEntity(*renderingComponent, position, angle);
		}

		TextComponent* textComponent = entity->GetComponent<TextComponent>();
		if (textComponent != nullptr && textComponent->IsVisible())
		{
			RenderText(*textComponent, position);
		}
	}
}

void Renderer::RenderEntity(const RenderingComponent& renderingComponent, const Vector2D& position, float angle) const
{
	Color color = renderingComponent.GetColor();
	std::vector<Vector2D> points = renderingComponent.GetGeometry();

	if (points.empty() || points.size() == 1)
	{
		return;
	}

	float angleInRadians = Utilities::ToRadians(angle);
	float cosA = cos(angleInRadians);
	float sinA = sin(angleInRadians);

	float x1, x2, y1, y2;

	for (int i = 0; i < points.size(); i++)
	{
		x1 = position.x + ((points[i].x * cosA) - (points[i].y * sinA));
		y1 = position.y + ((points[i].x * sinA) + (points[i].y * cosA));

		if (i < points.size() - 1)
		{
			x2 = position.x + ((points[i + 1].x * cosA) - (points[i + 1].y * sinA));
			y2 = position.y + ((points[i + 1].x * sinA) + (points[i + 1].y * cosA));
		}
		else
		{
			x2 = position.x + ((points[0].x * cosA) - (points[0].y * sinA));
			y2 = position.y + ((points[0].x * sinA) + (points[0].y * cosA));
		}

		App::DrawLine(x1, y1, x2, y2, color.red, color.green, color.blue);
	}
}

void Renderer::RenderText(const TextComponent& textComponent, const Vector2D& position) const
{
	Color color = textComponent.GetColor();
	App::Print(position.x, position.y, textComponent.GetText().c_str(), color.red, color.green, color.blue);
}

void Renderer::RenderBackground(Background & background) const
{
	CTable& table = background.GetTable();
	for (auto& line : table.m_lines)
	{
		const CLineDefinition& def = table.m_lineDefs[line.m_type];
		App::DrawLine(line.m_start.m_x, line.m_start.m_y, line.m_end.m_x, line.m_end.m_y, def.m_Red, def.m_Green, def.m_Blue);
	}
}
