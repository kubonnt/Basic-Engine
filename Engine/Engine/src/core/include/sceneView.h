#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include "scene.h"

namespace ECS
{
	template <typename... ComponentTypes>
	struct SceneView
	{
		SceneView(Scene& scene)
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

		struct Iterator
		{
			Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
				: pScene(pScene), index(index), mask(mask), all(all)
			{
			}

			EntityID operator*() const
			{
				return pScene->entities[index].id;
			}

			bool operator==(const Iterator& other) const
			{
				return index == other.index || index == pScene->entities.size();
			}

			bool operator!=(const Iterator& other) const
			{
				return index != other.index && index != pScene->entities.size();
			}

			Iterator& operator++()
			{
				do
				{
					++index;
				} while (index < pScene->entities.size() && !ValidIndex());

				return *this;
			}

			bool ValidIndex()
			{
				// It's a valid entity ID and it has the correct component mask
				return IsEntityValid(pScene->entities[index].id) && (all || mask == (mask & pScene->entities[index].mask));
			}

			EntityIndex index;
			Scene* pScene{nullptr};
			ComponentMask mask;
			bool all{ false };
		};
		
		Scene* poolScene{ nullptr };
		ComponentMask componentMask;
		bool all{ false };

		const Iterator begin() const
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

		const Iterator end() const
		{
			return Iterator(poolScene, EntityIndex(poolScene->entities.size()), componentMask, all);
		}
	};
}
#endif // !SCENE_VIEW_H
