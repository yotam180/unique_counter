#include <iostream>

#include "ComparisonCounted.h"

using CCInt = ComparisonCounted<int>;

int main()
{
	CCInt a = 5;
	CCInt b = 7;

	if (a < b)
	{
		std::cout << "Hello, world!" << std::endl;
	}

	std::cout << ComparisonCounter::get_comparisons_count() << " comparisons have been conducted\n";

	return 0;
}
