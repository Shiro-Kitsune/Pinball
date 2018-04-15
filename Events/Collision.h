#pragma once

class Entity;

class Collision
{
public:
	Collision(std::shared_ptr<Entity> entity);
	std::shared_ptr<Entity> GetCollidedEntity();
private:
	std::shared_ptr<Entity> m_collidedWith;
};
