#pragma once

#include "UniqueCounter.h"

template <class T>
class OriginalAlgorithmUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;

private:
	bool range_contains(std::vector<T>::iterator start, std::vector<T>::iterator end, T value);
};

template<class T>
inline size_t OriginalAlgorithmUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	const auto unique_start = array.begin();
	auto unique_end = array.begin();

	for (auto current = array.begin(); current != array.end(); ++current)
	{
		if (!range_contains(unique_start, unique_end, *current))
		{
			*unique_end = *current;
			unique_end++;
		}
	}

	return std::distance(unique_start, unique_end);
}

template<class T>
inline bool OriginalAlgorithmUniqueCounter<T>::range_contains(std::vector<T>::iterator start, std::vector<T>::iterator end, T value)
{
	return std::find(start, end, value) != end;
}
