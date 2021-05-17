#pragma once

/// <summary>
/// MetricsCounter meters performance of code in terms of placements (includes copies), value comparisons and
/// fixed calculations (such as hash computation)
/// </summary>
class MetricsCounter final
{
public:
	/// <summary>
	/// The following functions are used to log when a comparison/placement/fixed calculation takes place.
	/// It should not normally be called from user code, but is used by Metered<T> types.
	/// </summary>
	static void add_comparison() noexcept;
	static void add_placement() noexcept;
	static void add_fixed_calculation() noexcept;

	/// <summary>
	/// The following functions reset the meters. reset() must be called before starting measuring an algorithm.
	/// </summary>
	static void reset_all() noexcept;
	static void reset_comparisons() noexcept;
	static void reset_placements() noexcept;
	static void reset_fixed_calculations() noexcept;

	/// <summary>
	/// The following functions return the current state of the metrics.
	/// </summary>
	static size_t get_comparisons_count() noexcept;
	static size_t get_placements_count() noexcept;
	static size_t get_fixed_calculation_count() noexcept;

private:
	static size_t comparison_count;
	static size_t placement_count;
	static size_t fixed_calculation_count;
};
