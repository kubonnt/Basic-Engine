#include "../include/handle.h"

namespace memory
{
	constexpr inline bool Handle::operator==(const Handle& other) const
	{
		return index == other.index && counter == other.counter;
	}

	constexpr inline bool Handle::operator!=(const Handle& other) const
	{
		return !(*this == other);
	}

	constexpr bool Handle::IsValid() const
	{
		return !(index == 0 && counter == 0);
	}

	constexpr Handle::operator bool() const
	{
		return IsValid();
	}

	constexpr unsigned int Handle::Hash() const
	{
		return counter << INDEX_BITS | index;
	}
}