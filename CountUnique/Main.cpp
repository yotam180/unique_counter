#include <iostream>

#include "ComparisonCounted.h"
#include "OriginalAlgorithmUniqueCounter.h"

using CCInt = ComparisonCounted<int>;

int main()
{
	OriginalAlgorithmUniqueCounter<CCInt> algorithm;
	std::vector<CCInt> array{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };

	auto result = algorithm.count_unique(array);
	std::cout << "There are " << result << " unique items in the array.\n"
		"The algorithm took " << ComparisonCounter::get_comparisons_count() << " comparisons\n";

	return 0;
}
