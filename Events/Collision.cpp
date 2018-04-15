#include "stdafx.h"
#include "Collision.h"
#include "../Entity.h"

Collision::Collision(std::shared_ptr<Entity> entity)
{
	m_collidedWith = entity;
}

std::shared_ptr<Entity> Collision::GetCollidedEntity()
{
	return m_collidedWith;
}
