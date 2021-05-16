#pragma once

#include <algorithm>

#include "UniqueCounter.h"

template <class T>
class HeapsortUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;

private:
	void heapsort(std::vector<T>& array);
};

template<class T>
inline size_t HeapsortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	heapsort(array);
	return count_unique_in_ordered_array(array);
}

template<class T>
inline void HeapsortUniqueCounter<T>::heapsort(std::vector<T>& array)
{
	std::make_heap(array.begin(), array.end());
	for (auto heap_end = array.rbegin(); heap_end != array.rend(); ++heap_end)
	{
		std::pop_heap(array.begin(), heap_end.base());
	}
}
