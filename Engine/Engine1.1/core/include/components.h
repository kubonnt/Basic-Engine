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
}
#endif // COMPONENTS_H