#pragma once

#include "UniqueCounter.h"

template <class T>
class OriginalAlgorithmUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t OriginalAlgorithmUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	auto unique_end = array.begin();

	for (auto it = array.begin(); it != array.end(); ++it)
	{
		if (std::find(array.begin(), unique_end, *it) == unique_end)
		{
			*unique_end = *it;
			unique_end++;
		}
	}

	return std::distance(array.begin(), unique_end);
}
