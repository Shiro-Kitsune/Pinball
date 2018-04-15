#pragma once

#include "Events/Collision.h"
#include "Components/Component.h"

class Entity
{
public:
	Entity(unsigned int id);
	Entity(unsigned int id, const std::string& name);

	void AddComponent(std::unique_ptr<Component> component);

	template <typename T>
	T* GetComponent()
	{
		std::type_index index(typeid(T));
		if (m_components.count(std::type_index(typeid(T))) != 0)
		{
			T* t = static_cast<T*>(m_components[index].get());
			return t;
		}
		else
		{
			return nullptr;
		}
	}

	void AddCollision(const Collision& collision);
	const std::vector<Collision>& GetCollisions();
	void RemoveCollisionWithEntity(unsigned int entityId);
	void RemoveAllCollisions();

	unsigned int GetId() const;
	void MarkAsNeedsToBeRemoved();
	bool NeedsToBeRemoved() const;
	const std::string& GetName() const;

private:
	unsigned int m_id;
	std::string m_name;
	bool m_needsToBeRemoved;

	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	std::vector<Collision> m_collisions;
};
