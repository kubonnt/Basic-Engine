#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include "scene.h"

namespace ECS
{

	struct SceneView
	{
		template <typename... ComponentTypes>
		SceneView(Scene& scene);

		struct Iterator
		{
			Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all);

			EntityID operator*() const;

			bool operator==(const Iterator& other) const;

			bool operator!=(const Iterator& other) const;

			Iterator& operator++();

			bool ValidIndex();

			EntityIndex index;
			Scene* poolScene;
			ComponentMask mask;
			bool all{ false };
		};
		
		Scene* poolScene{ nullptr };
		ComponentMask componentMask;
		bool all{ false };

		const Iterator begin() const;
		const Iterator end() const;
	};
}

#endif
