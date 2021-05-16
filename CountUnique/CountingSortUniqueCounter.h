#pragma once

#include "UniqueCounter.h"
#include "MeteredTypes.h"


template <class T>
class CountingSortUniqueCounter final
	: public UniqueCounter<T>
{
private:
	// We use m_bool and m_size_t to measure access and update of elements inside the counting-sort C table
	using m_bool = Metered<bool>;
	using m_size_t = Metered <size_t>;

public:
	size_t count_unique(std::vector<T>& array) override;

public:
	// min_value is inclusive, max_value is exclusive - the allowed range is [min_value, max_value)
	explicit CountingSortUniqueCounter(size_t min_value, size_t max_value) :
		min_value(min_value), 
		max_value(max_value),
		present_table(max_value - min_value, false) {}

private:
	size_t min_value;
	size_t max_value;
	std::vector<m_bool> present_table;
};

template<class T>
inline size_t CountingSortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	m_size_t unique_count = 0;
	for (auto& el : array)
	{
		if (present_table[el.value()] == false) // == false is required so the comparison is counted
		{
			present_table[el.value()] = true;
			unique_count++;
		}
	}
	return unique_count.value();
}
