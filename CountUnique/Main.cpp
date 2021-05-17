#include "MeteredTypes.h"
#include "OriginalAlgorithmUniqueCounter.h"
#include "InsertionSortUniqueCounter.h"
#include "OptimalSortUniqueCounter.h"
#include "HeapsortUniqueCounter.h"
#include "CountingSortUniqueCounter.h"
#include "HashtableUniqueCounter.h"

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <random>

using m_int = Metered<int>;

constexpr auto MINIMUM_VALUE = 0, MAXIMUM_VALUE = 100;

static auto create_algorithms_vector()
{
	std::map<std::string, std::unique_ptr<UniqueCounter<m_int>>> algorithms;
	algorithms.emplace("1 Original algorithm", new OriginalAlgorithmUniqueCounter<m_int>());
	algorithms.emplace("2 Insertion sort", new InsertionSortUniqueCounter<m_int>());
	algorithms.emplace("3 Heap sort", new HeapsortUniqueCounter<m_int>());
	algorithms.emplace("4 Optimal sort", new OptimalSortUniqueCounter<m_int>());
	algorithms.emplace("5 Counting table", new CountingSortUniqueCounter<m_int>(MINIMUM_VALUE, MAXIMUM_VALUE + 1));
	algorithms.emplace("6 Hash table", new HashtableUniqueCounter<m_int>());
	return algorithms;
}

static void run_algorithm(const std::unique_ptr<UniqueCounter<m_int>>& algorithm, const std::vector<m_int>& given_array)
{
	MetricsCounter::reset_all();

	auto array = given_array; // Creating a copy
	auto unique_count = algorithm->count_unique(array);
	std::cout << "Result: " << unique_count << ", Comparisons: " << MetricsCounter::get_comparisons_count()
		<< ", Placements: " << MetricsCounter::get_placements_count() << ", Calculations: " << MetricsCounter::get_fixed_calculation_count()
		<< "\n";
}

static size_t prompt_array_length()
{
	std::cout << "N=";
	size_t array_length;
	std::cin >> array_length;
	return array_length;
}

static int generate_random(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<> distribution(min, max);

	return distribution(generator);
}

static std::vector<m_int> generate_array(size_t length)
{
	std::vector<m_int> vec;
	vec.reserve(length);
	for (size_t i = 0; i < length; ++i)
	{
		vec.push_back(generate_random(MINIMUM_VALUE, MAXIMUM_VALUE));
	}

	return vec;
}

int main()
{
	const auto algorithms = create_algorithms_vector();
	const auto array_length = prompt_array_length();
	const auto array = generate_array(array_length);
	
	for (const auto& algorithm : algorithms)
	{
		std::cout << "Running with " << algorithm.first << "\n\t";
		run_algorithm(algorithm.second, array);
	}

	return 0;
}
