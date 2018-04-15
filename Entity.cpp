#include "stdafx.h"
#include "Entity.h"

Entity::Entity(const unsigned int id) : m_id(id)
{
	m_needsToBeRemoved = false;
}

Entity::Entity(unsigned int id, const std::string& name) : m_id(id), m_name(name)
{
	m_needsToBeRemoved = false;
}

void Entity::AddComponent(std::unique_ptr<Component> component)
{
	m_components[std::type_index(typeid(*component.get()))] = std::move(component);
}

void Entity::AddCollision(const Collision& collision)
{
	m_collisions.push_back(collision);
}

const std::vector<Collision>& Entity::GetCollisions()
{
	return m_collisions;
}

void Entity::RemoveCollisionWithEntity(unsigned int entityId)
{
	auto position = std::find_if(m_collisions.begin(), m_collisions.end(),
		[entityId](Collision & collision) { return collision.GetCollidedEntity()->GetId() == entityId; });

	if (position != m_collisions.end())
	{
		m_collisions.erase(position);
	}
}

void Entity::RemoveAllCollisions()
{
	m_collisions.clear();
}

unsigned int Entity::GetId() const
{
	return m_id;
}

void Entity::MarkAsNeedsToBeRemoved()
{
	m_needsToBeRemoved = true;
}

bool Entity::NeedsToBeRemoved() const
{
	return m_needsToBeRemoved;
}

const std::string & Entity::GetName() const
{
	return m_name;
}