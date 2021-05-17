#pragma once

#include <unordered_set>

#include "UniqueCounter.h"
#include "MeteredTypes.h"

/// <summary>
/// Logging hash is a "proxy" hash that logs hash calculations using MetricsCounter. The hash calculations are counted for
/// MetricsCounter::get_fixed_calculation_count();
/// </summary>
/// <typeparam name="OriginalHash">The original hash type</typeparam>
/// <typeparam name="T">The original type which the original hash operates on</typeparam>
template <class OriginalHash, class T>
struct logging_hash
	: private OriginalHash
{
public:
	size_t operator()(const T& key) const {
		CALCULATION return OriginalHash::operator()(key);
	}
};

/// <summary>
/// This algorithm is in some way similar to CountingSortUniqueCounter, but it uses a hashset with chaining. For any element in the array,
/// we search for it in the hashtable, and if it's not found, we insert it into the table and increment the counter.
/// 
/// It has the advantage of not requiring prior knowledge on the range of values present in the array.
/// </summary>
template <class T, class Hasher = std::hash<T>>
class HashtableUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T, class Hasher>
inline size_t HashtableUniqueCounter<T, Hasher>::count_unique(std::vector<T>& array)
{
	// We allow ourselves to use std::unordered_set since the Microsoft STL implements it using a hash table
	// See https://github.com/microsoft/STL/blob/62137922ab168f8e23ec1a95c946821e24bde230/stl/inc/unordered_set

	size_t unique_count = 0;
	std::unordered_set<T, logging_hash<Hasher, T>> counted_values;
	for (auto& i : array)
	{
		if (counted_values.find(i) == counted_values.end())
		{
			counted_values.insert(i);
			unique_count++;
		}
	}
	return unique_count;
}
