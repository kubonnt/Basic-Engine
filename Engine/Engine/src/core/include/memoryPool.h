#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <memory>

constexpr int MAX_ENTITIES = 32;
		
namespace MemoryPool
{
	namespace ComponentPool
	{
		struct ComponentPool
		{
			ComponentPool(size_t elementSize);
			~ComponentPool();

			inline void* get(size_t index);

			char* poolData{ nullptr };
			size_t elementSize{ 0 };
		};
	}
}

#endif // !MEMORYPOOL_H

