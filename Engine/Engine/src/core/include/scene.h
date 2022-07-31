#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <bitset>

#include "memoryPool.h"

extern int m_componentCounter;

namespace ECS
{
	typedef unsigned long long EntityID;
	constexpr int MAX_COMPONENTS = 32;
	typedef std::bitset<MAX_COMPONENTS> ComponentMask;
	
	// For destroying and creating entities
	typedef unsigned int EntityIndex;
	typedef unsigned int EntityVersion;	

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

	// !!! Test purpose only !!! 
	struct TransformComponent
	{
		float position{ 1.f };
		float rotation{ 2.f };
	};

	struct Scene
	{
		// All the info we need about each entity
		struct EntityDesc
		{
			EntityID id;
			ComponentMask mask;
		};
		std::vector<EntityDesc> entities;
	
		std::vector<MemoryPool::ComponentPool::ComponentPool> componentPools;

		EntityID NewEntity();

		/*
		// Might delete that method in the future - needed this for debug/research purposes
		template <typename T>
		void AssignComponent(EntityID id);
		*/

		template <typename T>
		void RemoveComponent(EntityID id);

		template <typename T>
		T* AssignComponent(EntityID id);

		template <typename T>
		T* GetComponent(EntityID id);

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
}

#endif // !SCENE_H