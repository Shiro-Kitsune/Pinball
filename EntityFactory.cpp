#include "stdafx.h"

#include "EntityFactory.h"
#include "Entity.h"
#include "../Components/BallComponent.h"
#include "../Components/BoundingBox2D.h"
#include "../Components/BoundingCircle2D.h"
#include "../Components/FlipperComponent.h"
#include "../Components/RenderingComponent.h"
#include "../Components/RigidBody2D.h"
#include "../Components/TargetComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/Transform.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/LauncherComponent.h"
#include "table.h"
#include "../Components/Background.h"
#include "../Components/MovingPlatformComponent.h"

EntityFactory::EntityFactory() : m_nextId(1)
{
}

Entity EntityFactory::CreateFlipper(const Vector2D& position, FlipperComponent::FlipperSide flipperSide)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position, 0.0f));
	entity.AddComponent(std::make_unique<RigidBody2D>(Vector2D(), Vector2D(), 0.0f, true));

	std::vector<Vector2D> points;
	if (flipperSide == FlipperComponent::FlipperSide::Left)
	{
		entity.AddComponent(std::make_unique<FlipperComponent>(VK_LEFT, 100.0f, 45.0f, FlipperComponent::FlipperSide::Left));
		points.push_back(Vector2D(0, 0)); 
		points.push_back(Vector2D(120, 0));
	}
	else
	{
		entity.AddComponent(std::make_unique<FlipperComponent>(VK_RIGHT, 100.0f, 45.0, FlipperComponent::FlipperSide::Right));
		points.push_back(Vector2D(-120, 0));
		points.push_back(Vector2D(0, 0));
	}
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 0.0f), points));
	return entity;
}

Entity EntityFactory::CreateBall(const Vector2D& position)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position));
	entity.AddComponent(std::make_unique<RigidBody2D>(Vector2D(), Vector2D()));
	entity.GetComponent<RigidBody2D>()->SetGrounded(true);

	float radius = 15.0f;
	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 0.5)
	{
		float px = static_cast<float>(sin(ang) * radius);
		float py = static_cast<float>(-cos(ang) * radius);
		points.push_back(Vector2D(px, py));
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 1.0f), points));
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));
	entity.AddComponent(std::make_unique<BallComponent>(position));
	return entity;
}

Entity EntityFactory::CreateLauncher(const Vector2D & position, int launchKeyCode)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position));
	entity.AddComponent(std::make_unique<RigidBody2D>(Vector2D(), Vector2D(), 0.0f, true));
	entity.AddComponent(std::make_unique<LauncherComponent>(launchKeyCode, 50.0f, position.y));

	float halfWidth = 25.0f;
	float halfHeight = 50.0f;

	std::vector<Vector2D> points{ Vector2D(-halfWidth, halfHeight), Vector2D(halfWidth, halfHeight), Vector2D(halfWidth, -halfHeight), Vector2D(-halfWidth, -halfHeight) };
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 1.0f), points));

	return entity;
}

Entity EntityFactory::CreateBackground(const char * fileName)
{
	Entity entity(GenerateId());
	CTable table = Utilities::LoadBackground(fileName);
	entity.AddComponent(std::make_unique<Background>(table));
	return entity;
}

Entity EntityFactory::CreateTarget(const Vector2D& position, TargetType type)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position));
	float radius = 30.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));

	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 0.5)
	{
		float px = static_cast<float>(sin(ang) * radius);
		float py = static_cast<float>(-cos(ang) * radius);
		points.push_back(Vector2D(px, py));
	}

	float r, g, b;
	int value;

	switch (type) {
	case TargetType::Small:
		r = 0.6f;
		g = 0.2f;
		b = 0.9f;
		value = 100;
		break;

	case TargetType::Medium:
		r = 0.9f;
		g = 0.3f;
		b = 0.6f;
		value = 150;
		break;

	case TargetType::Large:
		r = 1.0f;
		g = 0.5f;
		b = 0.9f;
		value = 200;
		break;
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(r, g, b), points));
	entity.AddComponent(std::make_unique<TargetComponent>(value, Color(r, g, b), Color(1.0f, 1.0f, 1.0f)));

	return entity;
}

Entity EntityFactory::CreateStaticPlatform(const Vector2D & position, float width, float height)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position));

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	std::vector<Vector2D> points{ Vector2D(-halfWidth, halfHeight), Vector2D(halfWidth, halfHeight), Vector2D(halfWidth, -halfHeight), Vector2D(-halfWidth, -halfHeight) };
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 0.0f), points));
	entity.AddComponent(std::make_unique<BoundingBox2D>(width, height));

	return entity;
}

Entity EntityFactory::CreateMovingPlatform(const Vector2D & position, float width, float height)
{
	Entity entity(GenerateId());
	entity.AddComponent(std::make_unique<Transform>(position));

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	std::vector<Vector2D> points{ Vector2D(-halfWidth, halfHeight), Vector2D(halfWidth, halfHeight), Vector2D(halfWidth, -halfHeight), Vector2D(-halfWidth, -halfHeight) };
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 0.0f), points));
	entity.AddComponent(std::make_unique<BoundingBox2D>(width, height));
	entity.AddComponent(std::make_unique<MovingPlatformComponent>(position, width*2));
	entity.AddComponent(std::make_unique<RigidBody2D>(Vector2D(30.0f, 0.0f), Vector2D(), 0.0f, true));

	return entity;
}

Entity EntityFactory::CreateUIText(const Vector2D& position, const std::string& text, const Color& color, const std::string& name)
{
	Entity entity(GenerateId(), name);
	entity.AddComponent(std::make_unique<Transform>(position));
	entity.AddComponent(std::make_unique<TextComponent>(text, color));
	return entity;
}

Entity EntityFactory::CreateUIText(const Vector2D& position, const std::string& text, const Color& color)
{
	return CreateUIText(position, text, color, "");
}

Entity EntityFactory::CreateUIButton(const Vector2D& position, float width, float height, const std::string& text, const Color& color, const Color& hoverColor, const std::string& name)
{
	Entity entity(GenerateId(), name);
	entity.AddComponent(std::make_unique<Transform>(position));
	entity.AddComponent(std::make_unique<UIButtonComponent>(color, hoverColor));
	entity.AddComponent(std::make_unique<TextComponent>(text, color));

	float halfHeight = height / 2.0f;
	float padding = 5.0f;
	Vector2D p1(0 - padding, halfHeight + padding);
	Vector2D p2(width - padding, halfHeight + padding);
	Vector2D p3(width - padding, -halfHeight + padding);
	Vector2D p4(0 - padding, -halfHeight + padding);
	std::vector<Vector2D> points{ p1, p2, p3, p4 };

	entity.AddComponent(std::make_unique<RenderingComponent>(color, points));
	entity.AddComponent(std::make_unique<BoundingBox2D>(width, height));
	return entity;
}

void EntityFactory::ResetIdCounter()
{
	m_nextId = 1;
}

unsigned int EntityFactory::GenerateId()
{
	return m_nextId++;
}
