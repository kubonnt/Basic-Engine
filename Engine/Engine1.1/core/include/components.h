#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entity.h"

namespace ECS
{
	// Simple transform
	struct Transform
	{
		float position{ 0 };
		float rotation{ 0 };
		float scale{ 0 };
	};

	// Needed to use virtual inheritace, an interface is needed so that, the ComponentManager can tell a generic
	// ComponentArray that an entity has been destroyed, and that it needs to update its array mappings
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};
}
#endif // COMPONENTS_H