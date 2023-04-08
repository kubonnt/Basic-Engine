#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entity.h"

namespace ECS
{
	// Needed to use virtual inheritace, an interface is needed so that, the ComponentManager can tell a generic
	// ComponentArray that an entity has been destroyed, and that it needs to update its array mappings.
	// There is a list of every ComponentArray (one per component type), and you need to notify all of them when
	// an entity is destroyed so that it can remove the entity's data if it exists. The only way of multiple 
	// templated types is to keep a list of their common interface so that you can call EntityDestroyed() on all of them.
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ENGINE_API ComponentArray : public IComponentArray
	{
	public:
		void InsertData(Entity entity, T component)
		{
			//assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

			// Put new entry at the end and update the maps
			size_t newIndex = m_size;
			m_entityToIndexMap[entity] = newIndex;
			m_indexToEntityMap[newIndex] = entity;
			m_componentArray[newIndex] = component;
			++m_size;
		}

		void RemoveData(Entity entity)
		{
			assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

			// Copy element at the end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
			size_t indexOfLastElement = m_size - 1;
			m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

			// Update the map to point to move spot
			Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
			m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_entityToIndexMap.erase(entity);
			m_indexToEntityMap.erase(indexOfLastElement);

			--m_size;
		}

		T& GetData(Entity entity)
		{
			assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

			// Return a reference to the entity's component
			return m_componentArray[m_entityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				RemoveData(entity);
			}
		}

	private:
		// The packed array of components (of type T), set to a specified maximum amount,
		// matching the maximum number of entities allowed to exist simultaneously, so that 
		// each entity has a unique spot.
		std::array<T, MAX_ENTITIES> m_componentArray;

		// Unordered_map have a performance penalty because when you want to get the ID
		// of a component, to grab it from contiguous array, you have to request it from
		// the unordered_map, which is not contiguous. A good alternative would be to use arrays.
		// But the unordered_maps have the nice property of supporting find(), insert(), and delete(), 
		// which allow for asserting validity without "if(valid)" checks and it's a bit clearer 
		// than setting array elements to some "INVALID" value.

		// Map from an entity ID to an array index.
		std::unordered_map<Entity, size_t> m_entityToIndexMap;

		// Map from an array index to an entity ID.
		std::unordered_map<size_t, Entity> m_indexToEntityMap;

		// Total size of valid entries in the array
		size_t m_size;
	};

	class ENGINE_API ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component more than once.");

			// Add this component type to the component type map.
			m_componentTypes.insert({ typeName, m_nextComponentType });

			// Create a ComponentArray pointer and add it to the component arrays map.
			m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			// Increment the value so that the next component registered is different
			++m_nextComponentType;
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

			// Return this component's type - used for creating signatures 
			return m_componentTypes[typeName];
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			// Add component to the array for an entity
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			// Remove a component from the array for an entity
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			// Get a reference to a component from the array for an entity
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(Entity entity)
		{
			// Notify each component array that an entity has been destroyed
			// If it has a component for that entity, it will be removed
			for (auto const& pair : m_componentArrays)
			{
				auto const& component = pair.second;
				component->EntityDestroyed(entity);
			}
		}

	private:
		// Map from type string pointer to a component type.
		std::unordered_map<const char*, ComponentType> m_componentTypes{};

		// Map from type string pointer to a component array.
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;

		// The component type to be assigned to the next registered component - starting at 0.
		ComponentType m_nextComponentType{};

		// Function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
	};

}
#endif // COMPONENTS_H