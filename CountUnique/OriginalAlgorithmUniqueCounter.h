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
	static_assert(std::is_copy_assignable_v<T>, "Type of unique counted array must be copyable");

	size_t u_size = 1;
	for (size_t i = 1; i < array.size(); ++i)
	{
		bool u = true;
		for (size_t j = 0; j < u_size; ++j)
		{
			if (array[j] == array[i])
			{
				u = false;
			}
		}

		if (u)
		{
			u_size++;
			array[u_size] = array[i];
		}
	}

	return u_size;
}
