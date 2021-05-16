#pragma once

#include "MetricsCounter.h"

size_t MetricsCounter::comparison_count = 0;

void MetricsCounter::add_comparison()
{
	comparison_count++;
}

void MetricsCounter::reset_comparisons()
{
	comparison_count = 0;
}

void MetricsCounter::reset()
{
	reset_comparisons();
	reset_placements();
}

size_t MetricsCounter::get_comparisons_count()
{
	return comparison_count;
}

void MetricsCounter::add_placement()
{
	placement_count++;
}

void MetricsCounter::reset_placements()
{
	placement_count = 0;
}

size_t MetricsCounter::get_placements_count()
{
	return placement_count;
}
