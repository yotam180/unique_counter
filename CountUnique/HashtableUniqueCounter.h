#pragma once

#include <unordered_set>

#include "UniqueCounter.h"

template <class T>
struct logging_hash
	: private std::hash<T>
{
public:
	static size_t _Do_hash(const T& _Keyval) noexcept {
		std::cout << "Hash function called" << std::endl;
		return std::hash<T>::_Hash_representation(_Keyval);
	}
};

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
	std::unordered_set<T, Hasher> counted_values;
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
