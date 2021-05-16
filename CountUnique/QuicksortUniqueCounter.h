#pragma once

#include <algorithm>

#include "UniqueCounter.h"

/*
We do not treat quicksort as an optimal comparison-based sort, but as it usually performs very well
we are also interested in examining its performance.
*/
template <class T>
class QuicksortUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t QuicksortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	std::sort(array.begin(), array.end());
	return count_unique_in_ordered_array(array);
}
