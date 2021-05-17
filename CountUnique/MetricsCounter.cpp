#pragma once

#include "MetricsCounter.h"

size_t MetricsCounter::comparison_count = 0;
size_t MetricsCounter::placement_count = 0;
size_t MetricsCounter::fixed_calculation_count = 0;

void MetricsCounter::add_comparison() noexcept
{
	comparison_count++;
}

void MetricsCounter::add_placement() noexcept
{
	placement_count++;
}

void MetricsCounter::add_fixed_calculation() noexcept
{
	fixed_calculation_count++;
}

void MetricsCounter::reset_all() noexcept
{
	reset_comparisons();
	reset_placements();
	reset_fixed_calculations();
}

void MetricsCounter::reset_comparisons() noexcept
{
	comparison_count = 0;
}

void MetricsCounter::reset_placements() noexcept
{
	placement_count = 0;
}

void MetricsCounter::reset_fixed_calculations() noexcept
{
	fixed_calculation_count = 0;
}

size_t MetricsCounter::get_comparisons_count() noexcept
{
	return comparison_count;
}

size_t MetricsCounter::get_placements_count() noexcept
{
	return placement_count;
}

size_t MetricsCounter::get_fixed_calculation_count() noexcept
{
	return fixed_calculation_count;
}
\