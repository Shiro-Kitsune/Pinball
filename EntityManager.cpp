#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"

unsigned int EntityManager::AddEntity(Entity entity)
{
	unsigned int id = entity.GetId();
	m_entities.push_back(std::make_shared<Entity>(std::move(entity)));
	m_entityIndexLookup.emplace(id, m_entities.size() - 1);
	return id;
}

std::shared_ptr<Entity> EntityManager::FindEntityByName(const std::string & name)
{
	for (auto const& entity : m_entities)
	{
		if (entity->GetName() == name)
		{
			return entity;
		}
	}
	return nullptr;
}

std::shared_ptr<Entity> EntityManager::FindEntityById(const unsigned int id)
{
	auto position = m_entityIndexLookup.find(id);
	if (position != m_entityIndexLookup.end())
	{
		return m_entities.at(position->second);
	}
	return nullptr;
}

Entity* EntityManager::GetEntityAt(int index)
{
	return m_entities.at(index).get();
}

const std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities() const
{
	return m_entities;
}

int EntityManager::GetNumberOfEntities() const
{
	return static_cast<int>(m_entities.size());
}

bool EntityManager::RemoveEntityByName(const std::string& name)
{
	std::vector<std::shared_ptr<Entity>>::iterator position = std::find_if(m_entities.begin(), m_entities.end(),
		[name](const std::shared_ptr<Entity>& entity) { return entity->GetName() == name; });

	if (position != m_entities.end())
	{
		m_entities.erase(position);
		return true;
	}

	return false;
}

bool EntityManager::RemoveEntityById(unsigned int id)
{
	auto position = m_entityIndexLookup.find(id);
	if (position != m_entityIndexLookup.end())
	{
		m_entities.erase(m_entities.begin() + position->second);
		m_entityIndexLookup.erase(id);
		return true;
	}
	return false;
}

void EntityManager::RemoveEntityAtIndex(int index)
{
	m_entities.erase(m_entities.begin() + index);
}

void EntityManager::RemoveAllEntities()
{
	m_entities.clear();
}