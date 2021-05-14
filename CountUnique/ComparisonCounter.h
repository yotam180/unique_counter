#pragma once

class ComparisonCounter final
{
public:
	static void add_comparison();
	static void reset();
	static size_t get_comparisons_count();

private:
	static size_t comparison_count;
};
