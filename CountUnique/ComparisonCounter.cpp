#pragma once

#include "ComparisonCounter.h"

size_t ComparisonCounter::comparison_count = 0;

void ComparisonCounter::add_comparison()
{
	comparison_count++;
}

void ComparisonCounter::reset()
{
	comparison_count = 0;
}

size_t ComparisonCounter::get_comparisons_count()
{
	return comparison_count;
}
