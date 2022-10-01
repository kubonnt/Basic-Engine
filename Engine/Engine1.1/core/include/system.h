#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>

#include "entity.h"
#include "components.h"

namespace ECS
{
	// The System Manager is in charge of maintaining a record of registered systems and their signatures. When the system is registered,
	// it's added to the map with typeid(T).name(). That same key is used for a map of system pointers as well.
	// As with components, this approach requires a call to RegisterSystem() for every additional system type added. 
	// Every system needs to have a signature set for it so that the manager can add appropiate entities to each system's list of entities.
	// When an entity's signature has changed (due to components being added or removed), then the system's list of entities that it's 
	// tracking needs to be updated. If an entity that the system is tracking is destroyed, then it also needs to update the list.
	class SystemManager;

	// All of the managers (EntityManager, ComponentManager and SystemManager) need to talk to each other. Coordinator class acts as a mediator. 
	// This allows to have a single instance of the coordinator, and to use it to interface with all of the managers.
	// The Coordinator has pointers to each manager and does some meta-managing between them.
	class Coordinator;

	// Every system needs a list of entities, and some logic outside of the system (in the form of manager to maintain the list), so the System class behaves 
	// as a base class that every system can inherit from, which allows the SystemManager to keep a list of pointers to systems. Inheritance, but not virtual.
	class System
	{
	public:
		// std::set because each entity is unique, and a set is defined as having every element be unique. Second thing is that every entity is an integer
		// wchich makes for easy compares when inserting/removing from the set. Removing a specific entity from a list is O(n) because you have to start
		// at the beginning and possibly go to the end, while removing from a set is O(log n) because it's a binary tree. However, inserting to a list
		// is O(1) while inserting into a set is O(log n) as well. Morover, with the set I can only use insert() and erease() without needing to find the entity
		// while in the list I'd need to first find().
		std::set<Entity> m_entities;
	};
}

#endif // !SYSTEM_H

