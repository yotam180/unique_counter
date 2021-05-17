#pragma once

#include "UniqueCounter.h"
#include "MetricsCounter.h"

#include <set>

/// <summary>
/// Uses a red-black tree for storing the already-met values in the array.
/// 
/// The implementation uses std::set, since the MSVC STL implementation says that a set is an
/// "ordered red-black tree of key values, unique keys"
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class RedBlackTreeUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t RedBlackTreeUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	std::set<T> present_values;
	size_t unique_count = 0;

	for (const auto& i : array)
	{
		if (!present_values.contains(i))
		{
			present_values.insert(i);
			unique_count++;
		}
	}

	return unique_count;
}
