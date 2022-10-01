#include "../include/components.h"

namespace ECS
{
	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(Entity entity, T component)
		{
			assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

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

		T& GetData(Entity entity) const
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

		// Unordered_map have a performance penalty because when ones want to get the ID
		// of a component, to grab it from contiguous array, they have to request it from
		// the unordered_map, which is not contiguous. A good alternative would be to use arrays

		// Map from an entity ID to an array index.
		std::unordered_map<Entity, size_t> m_entityToIndexMap;

		// Map from an array index to an entity ID.
		std::unordered_map<size_t, Entity> m_indexToEntityMap;

		// Total size of valid entries in the array
		size_t m_size;
	};
}