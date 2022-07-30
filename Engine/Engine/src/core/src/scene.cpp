#include <iostream>

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
		entities.push_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
		return entities.back().id;
	}

	/*
	template <typename T>
	void Scene::AssignComponent(EntityID id)
	{
		int componentId = GetId<T>();
		entities[id].mask.set(componentId);
	}
	*/

	template <typename T>
	void Scene::RemoveComponent(EntityID id)
	{
		// Ensures we are not accessing entity that has been deleted
		if (entities[GetEntityIndex(id)].id != id)
			return;

		int componentId = GetId<T>();
		entities[GetEntityIndex(id)].mask.reset(componentId);
	}

	template <typename T>
	T* Scene::AssignComponent(EntityID id)
	{
		// Ensures we are not accessing entity that has been deleted
		if (entities[GetEntityIndex(id)].id != id)
			return;

		int componentId = GetId<T>();

		// First we check if there is a pool for this component
		if (componentPools.size() <= componentId) // Not enaugh component pool, resize the vector and create a new pool for that component
			componentPools.resize(componentId + 1, nullptr);

		// Second we can use new operator to call the ctor of the component at the correct memory location in the pool
		if (componentPools[componentId] == nullptr) // New component, make a new pool
			componentPools[componentId] = new MemoryPool::ComponentPool::ComponentPool(sizeof(T));

		// Looks up the component in the pool and initializes it with new 
		T* poolComponent = new (componentPools[componentId]->get(id)) T();

		// Set the bit for this component to true and return the created component
		entities[GetEntityIndex(id)].mask.set(componentId);
		return poolComponent;
	}

	template <typename T>
	T* Scene::GetComponent(EntityID id)
	{
		// Ensures we are not accessing entity that has been deleted
		if (entities[GetEntityIndex(id)].id != id)
			return;

		int componentId = GetId<T>();
		// Testing the bitmask before accessing the component pool. If I've removed a component by unsetting its bit, this will prevent me from accessing component's data that's not supposed to be assigned to this entity
		if (!entities[GetEntityIndex(id)].mask.test(componentId))
			return nullptr;

		T* poolComponent = static_cast<T*>(componentPools[componentId]->get(GetEntityIndex(id)));
		return poolComponent;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
		entities[GetEntityIndex(id)].id = newID;
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

	inline bool Scene::IsEntityValid(EntityID id)
	{
		// Check if the index is a valid index
		return (id >> 32) != EntityIndex(-1);
	}
}

int main(int argc, char *argv[])
{
	printf("TransformComponent ID: %i\n", ECS::GetId<ECS::TransformComponent>());
}