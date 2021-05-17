#pragma once

#include "UniqueCounter.h"
#include "MeteredTypes.h"

/// <summary>
/// Uses a counting-sort like table, but instead of holding counts, only holds booleans, with the meaning of 
/// "have we seen this value before?". On every iteration, we check if the element is already in the presence table, and if it's not,
/// we add it and increment the unique count.
/// 
/// Of course, this algorithm is limited since it has to know the valid ranage of values present in the array.
/// </summary>
template <class T>
class CountingSortUniqueCounter final
	: public UniqueCounter<T>
{
private:
	// We use m_bool to measure access and update of elements inside the counting-sort C table
	using m_bool = Metered<bool>;

public:
	size_t count_unique(std::vector<T>& array) override;

public:
	// min_value is inclusive, max_value is exclusive - the allowed range is [min_value, max_value)
	explicit CountingSortUniqueCounter(size_t min_value, size_t max_value) :
		min_value(min_value), 
		max_value(max_value),
		presence_table{} {}

private:
	void clear_presence_table();
	bool present_in_table(const T& key);
	void add_to_table(const T& key);
	size_t get_presence_table_index(const T& key);

private:
	size_t min_value;
	size_t max_value;
	std::vector<m_bool> presence_table;
};

template<class T>
inline size_t CountingSortUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	size_t unique_count = 0;
	clear_presence_table();

	for (auto& el : array)
	{
		if (!present_in_table(el)) 
		{
			add_to_table(el);
			unique_count++;
		}
	}

	return unique_count;
}

template<class T>
inline void CountingSortUniqueCounter<T>::clear_presence_table()
{
	presence_table.clear();
	presence_table.resize(max_value - min_value);
}

template<class T>
inline bool CountingSortUniqueCounter<T>::present_in_table(const T& key)
{
	return presence_table[get_presence_table_index(key)] == true; // == true is required so the comparison is counted
}

template<class T>
inline void CountingSortUniqueCounter<T>::add_to_table(const T& key)
{
	presence_table[get_presence_table_index(key)] = true;
}

template<class T>
inline size_t CountingSortUniqueCounter<T>::get_presence_table_index(const T& key)
{
	return static_cast<size_t>(key) - min_value;
}
