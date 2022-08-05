#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <bitset>

#include "memoryPool.h"

extern int m_componentCounter;

typedef unsigned long long EntityID;
constexpr int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;

// !!! Test purpose only !!! 
struct TransformComponent
{
	float position{ 1.f };
	float rotation{ 2.f };
};

namespace ECS
{
	// For destroying and creating entities

	/*
	------------------------ Creating and destroying entities -----------------------
	When creating entities we push them back to the Scene::entities vector.
	The problem occurs when we want to destroy them. We would remove the entity from
	the vector and that would be it. The problem is, when we create a new entity
	afterward, it'll be in the same slot as the previously deleted entity.
	A reference to the old entity could attempt to access data, and end up
	accidentally accessing data from the new entity. To protect against that
	I'll add an extra piece of info to entity IDs, a version number.

	We have a 64 bit entity ID, so we'll store the index of the entity in the
	top 32 bits, and the version number in the bottom 32 bits.
	---------------------------------------------------------------------------------
	*/

	inline bool IsEntityValid(EntityID id)
	{
		// Check if the index is a valid index
		return (id >> 32) != EntityIndex(-1);
	}

	template <class T>
	int GetId()
	{
		static int m_componentId = ++m_componentCounter;
		return m_componentId;
	}
	
	using namespace MemoryPool::ComponentPool;

	struct Scene
	{
		// All the info we need about each entity
		struct Entity
		{
			EntityID id;
			ComponentMask mask;
		};
		std::vector<Entity> entities;
	
		std::vector<ComponentPool*> componentPools;

		EntityID NewEntity();

		/*
		// Might delete that method in the future - needed this for debug/research purposes
		template <typename T>
		void AssignComponent(EntityID id);
		*/

		template <typename T>
		T* AssignComponent(EntityID id)
		{
			// Ensures we are not accessing entity that has been deleted
			if (entities[GetEntityIndex(id)].id != id)
				return nullptr;

			int componentId = GetId<T>();

			// First we check if there is a pool for this component
			if (componentPools.size() <= componentId) // Not enaugh component pool, resize the vector and create a new pool for that component
			{
				componentPools.resize(componentId + 1, 0);
			}

			// Second we can use the new operator to call the ctor of the component at the correct memory location in the pool
			if (componentPools[componentId] == nullptr) // New component, make a new pool
			{
				componentPools[componentId] = new ComponentPool(sizeof(T));
			}

			// Looks up the component in the pool and initializes it with the new 
			T* poolComponent = new (componentPools[componentId]->get(id)) T();

			// Set the bit for this component to true and return the created component
			entities[GetEntityIndex(id)].mask.set(componentId);
			return poolComponent;
		}

		template <typename T>
		T* GetComponent(EntityID id)
		{
			// Ensures we are not accessing entity that has been deleted
			if (entities[GetEntityIndex(id)].id != id)
				return nullptr;

			int componentId = GetId<T>();
			// Testing the bitmask before accessing the component pool. If I've removed a component by unsetting its bit, this will prevent me from accessing component's data that's not supposed to be assigned to this entity
			if (!entities[GetEntityIndex(id)].mask.test(componentId))
				return nullptr;

			T* poolComponent = static_cast<T*>(componentPools[componentId]->get(GetEntityIndex(id)));
			return poolComponent;
		}

		template <typename T>
		void RemoveComponent(EntityID id)
		{
			// Ensures we are not accessing entity that has been deleted
			if (entities[GetEntityIndex(id)].id != id)
				return;

			int componentId = GetId<T>();
			entities[GetEntityIndex(id)].mask.reset(componentId);
		}

		std::vector<EntityIndex> freeEntities;
		/*
		-----------------------------------------------------------------------------------------------------
		freeEntities - used to keep record of what entity IDs are free and can be used when creating new ones
		Thanks to that deleting an entity amounts to setting the entity slot to an invalid index
		and incementing the version number. Then add another element to the free list. Also clear the mask
		-----------------------------------------------------------------------------------------------------
		*/

		void DestroyEntity(EntityID id);

		inline EntityID CreateEntityId(EntityIndex index, EntityVersion version);

		inline EntityIndex GetEntityIndex(EntityID id);

		inline EntityVersion GetEntityVersion(EntityID id);

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)
	};

	template Scene* Scene::GetComponent<>(EntityID id);
	template void Scene::RemoveComponent<Scene>(EntityID id);
	template Scene* Scene::AssignComponent<>(EntityID id);

}

#endif // !SCENE_H