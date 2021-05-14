#pragma once

#include <vector>

template <class T>
class UniqueCounter
{
public:
	virtual size_t count_unique(std::vector<T>& array) = 0;
};
