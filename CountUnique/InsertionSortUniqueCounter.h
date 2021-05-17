#pragma once

#include "UniqueCounter.h"

#include <algorithm>

/// <summary>
/// Uses insertion sort to sort the array, then iterates the array and finds the unique count in linear time
/// </summary>
template <class T>
class InsertionSortUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;

private:
	void insertion_sort(std::vector<T>& array) const;
};

template<class T>
inline size_t InsertionSortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	insertion_sort(array);
	return count_unique_in_ordered_array(array);
}

template<class T>
inline void InsertionSortUniqueCounter<T>::insertion_sort(std::vector<T>& array) const
{
	for (auto it = array.begin(); it != array.end(); ++it)
	{
		auto first_larger = std::upper_bound(array.begin(), it, *it);
		std::rotate(first_larger, it, it + 1);
	}
}
