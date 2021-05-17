#pragma once

#include "BinaryTree.h"
#include "UniqueCounter.h"

template <class T>
class BinaryTreeUniqueCounter final
	: public UniqueCounter<T>
{
public:
	size_t count_unique(std::vector<T>& array) override;
};

template<class T>
inline size_t BinaryTreeUniqueCounter<T>::count_unique(std::vector<T>& array)
{
	BinaryTree<T> tree;
	size_t unique_count = 0;

	for (const auto& i : array)
	{
		if (!tree.contains(i))
		{
			tree.insert(i);
			unique_count++;
		}
	}

	return unique_count;
}
