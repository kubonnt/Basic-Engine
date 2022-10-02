#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>

#include "entity.h"
#include "components.h"

namespace ECS
{
	// Every system needs a list of entities, and some logic outside of the system (in the form of manager to maintain the list), so the System class behaves 
	// as a base class that every system can inherit from, which allows the SystemManager to keep a list of pointers to systems. Inheritance, but not virtual.
	struct System
	{
		// std::set because each entity is unique, and a set is defined as having every element be unique. Second thing is that every entity is an integer
		// wchich makes for easy compares when inserting/removing from the set. Removing a specific entity from a list is O(n) because you have to start
		// at the beginning and possibly go to the end, while removing from a set is O(log n) because it's a binary tree. However, inserting to a list
		// is O(1) while inserting into a set is O(log n) as well. Morover, with the set I can only use insert() and erase() without the need of finding
		// the entity, while in the list I'd need to find() first.
		std::set<Entity> m_entities;
	};

	// The System Manager is in charge of maintaining a record of registered systems and their signatures. When the system is registered,
	// it's added to the map with typeid(T).name(). That same key is used for a map of system pointers as well.
	// As with components, this approach requires a call to RegisterSystem() for every additional system type added. 
	// Every system needs to have a signature set for it so that the manager can add appropiate entities to each system's list of entities.
	// When an entity's signature has changed (due to components being added or removed), then the system's list of entities that it's 
	// tracking needs to be updated. If an entity that the system is tracking is destroyed, then it also needs to update the list.
	class SystemManager;

	// All of the managers (EntityManager, ComponentManager and SystemManager) need to talk to each other. Coordinator class acts as a mediator. 
	// This allows to have a single instance of the coordinator, and to use it to interface with all of the managers.
	// The Coordinator has pointers to each manager and does some meta-managing between them.
	class Coordinator;

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

			// Create a pointer to the system and return it so it can be used externally.
			auto system = std::make_shared<T>();
			m_systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

			// Set signature for this system.
			m_signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			// Erase a destroyed entity from all system lists.
			// m_entities is a set, so no checks needed.
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;
				system->m_entities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			// Notify each system that an entity's signature has changed.
			for (auto const& pair : m_systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_signatures[type];

				// Entity signature matches system signature - insert into the set.
				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_entities.insert(entity);
				}
				else
				{
					system->m_entities.erase(entity);
				}
			}
		}

	private:
		// Map from system type string pointer to a signature.
		std::unordered_map<const char*, Signature> m_signatures{};

		// Map from system type string pointer to a system pointer.
		std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
	};

	class Coordinator
	{
	public:
		void Init()
		{
			// Create pointers to each manager.
			m_componentManager = std::make_unique<ComponentManager>();
			m_entityManager = std::make_unique<EntityManager>();
			m_systemManager = std::make_unique<SystemManager>();
		}

		// Entity methods.
		Entity CreateEntity()
		{
			return m_entityManager->CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			m_entityManager->DestroyEntity(entity);
			m_componentManager->EntityDestroyed(entity);
			m_systemManager->EntityDestroyed(entity);
		}

		// Component methods.
		template<typename T>
		void RegisterComponent()
		{
			m_componentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			m_componentManager->AddComponent<T>(entity, component);

			auto signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), true);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			m_componentManager->RemoveComponent<T>(entity);

			auto signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), false);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return m_componentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return m_componentManager->GetComponentType<T>();
		}

		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_systemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			m_systemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
	};

}

#endif // !SYSTEM_H

