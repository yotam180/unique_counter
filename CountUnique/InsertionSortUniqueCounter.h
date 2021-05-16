#pragma once

#include <algorithm>

#include "UniqueCounter.h"

template <class T>
class InsertionSortUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t InsertionSortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	for (auto it = array.begin(); it != array.end(); ++it)
	{
		auto first_larger = std::upper_bound(array.begin(), it, *it);
		std::rotate(first_larger, it, it + 1);
	}
	
	return count_unique_in_ordered_array(array);
}
