#include "../include/scene.h"

int m_componentCounter = 0;

//using namespace ESC;
namespace ECS
{
	EntityID Scene::NewEntity()
	{
		// Check the freeEntities list and if there is a free slot -> reuse
		if (!freeEntities.empty())
		{
			EntityIndex newIndex = freeEntities.back();
			freeEntities.pop_back();
			EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
			entities[newIndex].id = newID;
			return entities[newIndex].id;
		}
		entities.push_back({ CreateEntityId(EntityID(entities.size()), 0), ComponentMask() });
		return entities.back().id;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		assert(id < entities.size());
		EntityID newID = INVALID_ENTITY;
		entities[id].id = newID;
		assert(entities[GetEntityIndex(id)].id != id);
		entities[GetEntityIndex(id)].mask.reset();
		freeEntities.push_back(GetEntityIndex(id));
	}

	inline EntityID Scene::CreateEntityId(EntityIndex index, EntityVersion version)
	{
		// Shift the index up 32 bits and put the version in the bottom
		return static_cast<EntityID>(index) << 32 | static_cast<EntityID>(version);
	}

	inline EntityIndex Scene::GetEntityIndex(EntityID id)
	{
		// Shift down 32 bits so to lose the version and get the index
		return id >> 32;
	}

	inline EntityVersion Scene::GetEntityVersion(EntityID id)
	{
		// Cast to a 32 bit int to get version number losing the top 32 bits
		return static_cast<EntityVersion>(id);
	}
}

