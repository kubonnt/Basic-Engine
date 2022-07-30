#include "../include/sceneView.h"

namespace ECS
{
	template <typename... ComponentTypes>
	SceneView::SceneView(Scene& scene) 
		: poolScene(&scene)
	{
		if (sizeof...(ComponentTypes) == 0)
		{
			all = true;
		}
		else
		{
			// Unpack the template parameters into an initializer list 
			int componentIds[] = { 0, GetId<ComponentTypes>() ... };
			for (int i = 1; i < (sizeof...(ComponentTypes) + 1); ++i)
				componentMask.set(componentIds[i]);
		}
	}

	SceneView::Iterator::Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
		: poolScene(pScene), index(index), mask(mask), all(all)
	{
	}

	EntityID SceneView::Iterator::operator*() const
	{
		return poolScene->entities[index].id;
	}

	bool SceneView::Iterator::operator==(const Iterator& other) const
	{
		return index == other.index || index == poolScene->entities.size();
	}

	bool SceneView::Iterator::operator!=(const Iterator& other) const
	{
		return index != other.index && index != poolScene->entities.size();
	}

	SceneView::Iterator& SceneView::Iterator::operator++()
	{
		do
		{
			++index;
		} while (index < poolScene->entities.size() && !ValidIndex());

		return *this;
	}

	bool SceneView::Iterator::ValidIndex()
	{
		// It's a valid entity ID and it has the correct component mask
		return IsEntityValid(poolScene->entities[index].id) && (all || mask == (mask & poolScene->entities[index].mask));
	}

	const SceneView::Iterator SceneView::begin() const
	{
		int firstIndex = 0;
		while (firstIndex < poolScene->entities.size() &&
			(componentMask != (componentMask & poolScene->entities[firstIndex].mask)
				|| !IsEntityValid(poolScene->entities[firstIndex].id)))
		{
			++firstIndex;
		}
		return Iterator(poolScene, firstIndex, componentMask, all);
	}

	const SceneView::Iterator SceneView::end() const
	{
		return Iterator(poolScene, EntityIndex(poolScene->entities.size()), componentMask, all);
	}
}