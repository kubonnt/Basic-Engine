#include "../include/system.h"
#include "../src/components.cpp" // Needed for ComponentManager - will resolve that later

namespace ECS
{
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
			m_systems.insert({typeName, system});
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

			// Set signature for this system.
			m_signatures.insert({typeName, signature});
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
		T& GetComponent(Entity entity) const
		{
			return m_componentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType() const
		{
			return m_componentManager->GetComponentType<T>();
		}

		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_systemManager->RegisterSystem<T>;
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