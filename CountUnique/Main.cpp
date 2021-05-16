#include <iostream>

#include "MeteredTypes.h"
#include "OriginalAlgorithmUniqueCounter.h"
#include "InsertionSortUniqueCounter.h"
#include "QuicksortUniqueCounter.h"
#include "HeapsortUniqueCounter.h"
#include "CountingSortUniqueCounter.h"

using CCInt = Metered<int>;

int main()
{
	CountingSortUniqueCounter<CCInt> algorithm(0, 10);
	std::vector<CCInt> array{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };

	auto result = algorithm.count_unique(array);
	std::cout << "There are " << result << " unique items in the array.\n"
		"The algorithm took " << MetricsCounter::get_comparisons_count() << " comparisons\n";

	return 0;
}
