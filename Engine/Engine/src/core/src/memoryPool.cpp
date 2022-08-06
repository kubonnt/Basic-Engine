#include "../include/memoryPool.h"
#include "../include/scene.h"

namespace MemoryPool
{
	namespace ComponentPool
	{
		ComponentPool::ComponentPool(size_t inElementSize)
		{
			// Allocating enough memory to hold MAX_ENTITIES, each with element size
			elementSize = inElementSize;
			poolData = new char[(elementSize* MAX_ENTITIES)];
		}

		ComponentPool::~ComponentPool()
		{
			delete[] poolData;
		}

		inline void* ComponentPool::get(size_t index)
		{
			return poolData + index * MAX_ENTITIES;
			
		}
	}
}