#pragma once

#include <algorithm>

#include "UniqueCounter.h"

/// <summary>
/// std::sort is guaranteed to be an optimal sorting algorithm (i.e. worst-time complexity of n*lg(n)) since C++11.
/// It is also known to be very fast, and it would be interesting to see what differences would std::sort and a handcrafted
/// heap sort have.
/// </summary>
template <class T>
class OptimalSortUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t OptimalSortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	std::sort(array.begin(), array.end());
	return count_unique_in_ordered_array(array);
}
