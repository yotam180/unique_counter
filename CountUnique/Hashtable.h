#pragma once

#include <functional>
#include <vector>
#include <list>

template <class T>
class Hashtable final
{
public:
	using HashFunc = std::function<size_t(const T&)>;

public:
	explicit Hashtable(size_t max_hash_value, HashFunc hash_function) :
		hash_function(hash_function),
		table(max_hash_value) {}

public:
	void insert(const T& value)
	{
		table[hash_function(value)].emplace_back(value);
	}

private:
	HashFunc hash_function;
	std::vector<std::list<T>> table;
};