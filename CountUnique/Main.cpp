#include "MeteredTypes.h"
#include "OriginalAlgorithmUniqueCounter.h"
#include "InsertionSortUniqueCounter.h"
#include "OptimalSortUniqueCounter.h"
#include "HeapsortUniqueCounter.h"
#include "CountingSortUniqueCounter.h"
#include "HashtableUniqueCounter.h"

#include <iostream>
#include <memory>

using m_int = Metered<int>;

static auto create_algorithms_vector()
{
	std::vector<std::unique_ptr<UniqueCounter<m_int>>> algorithms;
	algorithms.emplace_back(new OriginalAlgorithmUniqueCounter<m_int>());
	algorithms.emplace_back(new InsertionSortUniqueCounter<m_int>());
	algorithms.emplace_back(new HeapsortUniqueCounter<m_int>());
	algorithms.emplace_back(new OptimalSortUniqueCounter<m_int>());
	algorithms.emplace_back(new CountingSortUniqueCounter<m_int>(1, 8)); // TODO: Adjust values
	algorithms.emplace_back(new HashtableUniqueCounter<m_int>());
	return algorithms;
}

void run_algorithm(const std::unique_ptr<UniqueCounter<m_int>>& algorithm, const std::vector<m_int>& given_array)
{
	MetricsCounter::reset_all();

	auto array = given_array; // Creating a copy
	auto unique_count = algorithm->count_unique(array);
	std::cout << "Result: " << unique_count << ", Comparisons: " << MetricsCounter::get_comparisons_count()
		<< ", Placements: " << MetricsCounter::get_placements_count() << ", Calculations: " << MetricsCounter::get_fixed_calculation_count()
		<< "\n";
}

int main()
{
	const auto algorithms = create_algorithms_vector();

	std::vector<m_int> array{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
	
	for (const auto& algorithm : algorithms)
	{
		run_algorithm(algorithm, array);
	}

	return 0;
}
