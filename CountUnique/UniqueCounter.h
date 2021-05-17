#pragma once

#include <vector>

/// <summary>
/// UniqueCounter is a simple base class for all algorithms. It only provides an interface containing a count_unique(...) function.
/// </summary>
template <class T>
class UniqueCounter
{
public:
	virtual size_t count_unique(std::vector<T>& array) = 0;

public:
	virtual ~UniqueCounter() = default;
};

/// <summary>
/// This function assumes the given array is sorted, iterates it once and returns the count of unique elements.
/// Time complexity is \Theta(n)
/// </summary>
template <class T>
size_t count_unique_in_ordered_array(const std::vector<T>& array)
{
	size_t unique_count = 0;
	for (auto it = array.cbegin(); it != array.cend(); ++it)
	{
		if (it == array.cbegin() || *it != *std::prev(it))
		{
			unique_count++;
		}
	}

	return unique_count;
}
