#ifndef HANDLE_H
#define HANDLE_H

#include <functional>

// Properties of a handle: 
// relocatebilty
// deletability, ABA problem
// serialisebility
// fast access

namespace memory
{
	struct Handle
	{
		static constexpr int INDEX_BITS = 16;
		static constexpr int COUNTER_BITS = 16;

		Handle() : index (0), counter(0) {}
		Handle(unsigned int i, unsigned int c) : index(i), counter(c) {}

		constexpr inline bool operator==(const Handle& other) const;
		constexpr inline bool operator!=(const Handle& other) const;

		constexpr bool IsValid() const;
		constexpr operator bool() const;
		constexpr unsigned int Hash() const;

		unsigned int index : INDEX_BITS;
		unsigned int counter : COUNTER_BITS;
	};
}

namespace std
{
	template<> 
	struct hash<memory::Handle>
	{
		size_t operator()(const memory::Handle& size) const noexcept
		{
			return size.Hash();
		}
	};
}

#endif // !HANDLE_H

