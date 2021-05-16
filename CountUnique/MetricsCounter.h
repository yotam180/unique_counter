#pragma once

class MetricsCounter final
{
public:
	static void add_comparison();
	static void reset_comparisons();
	static size_t get_comparisons_count();

	static void add_placement();
	static void reset_placements();
	static size_t get_placements_count();

	static void reset();
private:
	static size_t comparison_count;
	static size_t placement_count;
};
