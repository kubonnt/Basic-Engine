#ifndef ENTITY_H
#define ENTITY_H

#include "core.h"

#include <cstdint>
#include <array>
#include <queue>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <typeinfo> 

namespace ECS
{
	typedef unsigned int Entity; // the Entity which is just and an ID 
	typedef unsigned char ComponentType;

	static constexpr ComponentType MAX_COMPONENTS = 32;
	static constexpr Entity MAX_ENTITIES = 5000;

	typedef std::bitset<MAX_COMPONENTS> Signature;

	class ENGINE_API EntityManager
	{
	public:
		EntityManager();
	
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void SetSignature(Entity entity, Signature signature);
		Signature GetSignature(Entity entity) const;

	private:
		// Queue of unused entity IDs
		std::queue<Entity> m_availableEntities{};

		// Array of signatures where the index corresponds to the entity ID
		std::array<Signature, MAX_ENTITIES> m_signatures{};

		// Total living entities - used to keep limits on how many exist
		unsigned int m_livingEntityCount{};
	};
}

#endif // !ENTITY_H