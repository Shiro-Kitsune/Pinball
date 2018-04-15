#pragma once

#include "FlipperComponent.h"
class Entity;
enum class TargetType;
enum class FlipperComponent::FlipperSide;

class EntityFactory
{
public:
	EntityFactory();
	Entity CreateFlipper(const Vector2D & position, FlipperComponent::FlipperSide flipperSide);
	Entity CreateBall(const Vector2D & position);
	Entity CreateLauncher(const Vector2D& position, int launchKeyCode);
	Entity CreateBackground(const char * fileName);
	Entity CreateAccelerator(const Vector2D & position);
	Entity CreateTarget(const Vector2D & position, TargetType type);
	Entity CreateStaticPlatform(const Vector2D & position, float width, float height);
	Entity CreateMovingPlatform(const Vector2D & position, float width, float height);
	Entity CreateSeed(const Vector2D & position);
	Entity CreateFlower(const Vector2D & position);
	Entity CreateTeleport(const Vector2D & position);
	Entity CreateUIText(const Vector2D & position, const std::string& text, const Color & color, const std::string& name);
	Entity CreateUIText(const Vector2D & position, const std::string& text, const Color & color);
	Entity CreateUIButton(const Vector2D & position, float width, float height, const std::string& text, const Color & color, const Color & hoverColor, const std::string& name);
	void ResetIdCounter();
private:
	unsigned int GenerateId();
private:
	unsigned int m_nextId;
};