#pragma once

#include <vector>

template <class T>
class UniqueCounter
{
public:
	virtual size_t count_unique(std::vector<T>& array) = 0;
};

// TODO: Move to a better place
template <class T>
size_t count_unique_in_ordered_array(const std::vector<T>& array)
{
	size_t unique_count = 0;
	for (auto it = array.cbegin(); it != array.cend(); ++it)
	{
		if (it == array.cbegin() || *it == *std::prev(it))
		{
			unique_count++;
		}
	}

	return unique_count;
}
