#include "stdafx.h"
#include "UIButtonSystem.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "Entity.h"
#include "GameState.h"
#include "UIButtonComponent.h"
#include "Event.h"
#include "RenderingComponent.h"
#include "TextComponent.h"
#include "Transform.h"
#include "BoundingBox2D.h"

void UIButtonSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	for (auto& entity : entityManager.GetEntities())
	{
		UIButtonComponent* buttonComponent = entity->GetComponent<UIButtonComponent>();
		BoundingBox2D* boundingBox = entity->GetComponent<BoundingBox2D>();
		Transform* transform = entity->GetComponent<Transform>();
		if (buttonComponent == nullptr || boundingBox == nullptr || transform == nullptr)
		{
			continue;
		}

		if (IsMouseOverButton(*transform, *boundingBox))
		{
			ChangeButtonColor(*entity, buttonComponent->GetHoverColor());

			if (App::IsKeyPressed(VK_LBUTTON))
			{
				eventManager.AddEvent(std::make_unique<UIEvent>(entity->GetName()));
			}
		}
		else
		{
			ChangeButtonColor(*entity, buttonComponent->GetColor());
		}
	}
}

bool UIButtonSystem::IsMouseOverButton(const Transform& transform, const BoundingBox2D& boundingBox)
{
	float x = transform.GetPosition().x;
	float y = transform.GetPosition().y;
	float width = boundingBox.GetWidth();
	float halfHeight = boundingBox.GetHalfHeight();
	float padding = 5.0f;
	Vector2D p1(x - padding, y + halfHeight + padding);
	Vector2D p2(x + width - padding, y + halfHeight + padding);
	Vector2D p3(x + width - padding, y - halfHeight + padding);
	Vector2D p4(x - padding, y - halfHeight + padding);

	float mouseX, mouseY;
	App::GetMousePos(mouseX, mouseY);
	Vector2D mousePoint(mouseX, mouseY);

	bool b1, b2;

	b1 = IsPointInTriangle(mousePoint, p1, p2, p3);
	b2 = IsPointInTriangle(mousePoint, p1, p4, p3);

	return (b1 || b2);
}

bool UIButtonSystem::IsPointInTriangle(const Vector2D& mousePoint, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3)
{
	bool b1, b2, b3;

	b1 = Sign(mousePoint, p1, p2) < 0.0f;
	b2 = Sign(mousePoint, p2, p3) < 0.0f;
	b3 = Sign(mousePoint, p3, p1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

float UIButtonSystem::Sign(const Vector2D& mousePoint, const Vector2D& p1, const Vector2D& p2)
{
	return (mousePoint.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (mousePoint.y - p2.y);
}

void UIButtonSystem::ChangeButtonColor(Entity& entity, const Color& color)
{
	RenderingComponent* renderingComponent = entity.GetComponent<RenderingComponent>();
	if (renderingComponent != nullptr)
	{
		renderingComponent->SetColor(color);
	}

	TextComponent* textComponent = entity.GetComponent<TextComponent>();
	if (textComponent != nullptr)
	{
		textComponent->SetColor(color);
	}
}