#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

namespace MemoryPool
{
	namespace ComponentPool
	{
		constexpr int MAX_ENTITIES = 32;

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

