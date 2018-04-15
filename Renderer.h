#pragma once

class EntityManager;
class RenderingComponent;
class UITextComponent;
class ParticleEmmiter;
class CTable;
class TextComponent;
class Background;

class Renderer
{
public:
	void Render(const EntityManager& entityManager) const;
private:
	void RenderEntity(const RenderingComponent& renderingComponent, const Vector2D& position, float angle) const;
	void RenderText(const TextComponent& textComponent, const Vector2D& position) const;
	void RenderBackground(Background& background) const;
};