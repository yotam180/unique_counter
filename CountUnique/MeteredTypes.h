#pragma once

#include "MetricsCounter.h"

#include <functional>

/// <summary>
/// Metered<T> is a wrapper around T, which counts comparisons and placements of T objects.
/// A consumer of this class should use MetricsCounter::get_xxx_count() to get the comparison/placement
/// counter for these types.
/// 
/// All objects of all metered types add to the same comparison counter. There is no per-object or per-type counters
/// to preserve simplicity.
/// </summary>
template <class T>
class Metered final
{
public:
	using This = Metered<T>;

public:

	/// <summary>
	/// This constructor is here to allow arbitrary object construction in a transparent way (not explicitly going through Metered<int> ctor).
	/// It enables us to do the following:
	/// 
	///		Metered<int> x = 5;
	/// 
	/// Instead of:
	/// 
	///		Metered<int> x{{5}};
	/// </summary>
	template <class ... Args>
	Metered(Args ...args) noexcept :
		inner_value(args...)
	{
		// We count a construction of a metered object as a placement in order to count the initial array initialization.
		// Otherwise, algorithms that require dynamic allocations will not be metered correctly (since the new allocations
		// would not be counted)
		PLACE
	}

public:
	// The following functions just wrap the native comparison check operators, and log the comparison
	bool operator==(T other) const noexcept { COMP return inner_value == other; }
	bool operator==(This other) const noexcept { COMP return inner_value == other.inner_value; }
	bool operator!=(This other) const noexcept { COMP return inner_value != other.inner_value; }
	bool operator>=(This other) const noexcept { COMP return inner_value >= other.inner_value; }
	bool operator>(This other) { COMP return inner_value > other.inner_value; }
	bool operator<=(This other) { COMP return inner_value <= other.inner_value; }
	bool operator<(This other) { COMP return inner_value < other.inner_value; }

	// The following functions wrap the native placement, increment, decrement operators and log a placement
	This& operator=(This other) noexcept
	{
		PLACE
		inner_value = other.inner_value;
		return *this;
	}

	T operator++(int) noexcept
	{
		PLACE
		T temp = inner_value;
		inner_value++;
		return temp;
	}

	This& operator++() noexcept
	{
		PLACE
		inner_value++;
		return *this;
	}

	T operator--(int) noexcept
	{
		PLACE
		T temp = value;
		inner_value--;
		return temp;
	}

	This& operator--() noexcept
	{
		PLACE
		inner_value--;
		return *this;
	}

	// Implicit and explicit conversions to the underlying type
	operator const T&() const noexcept 
	{
		return inner_value;
	}
	
	T value() noexcept
	{
		return inner_value;
	}

private:
	T inner_value;

private:
	friend struct std::hash<This>;
};

namespace std
{
	/// <summary>
	/// Used for stl unordered associative containers requiring a hash function. This template specialization
	/// is provided to make Metered<T> a transparent substitution for T.
	/// </summary>
	template <class T>
	struct hash<Metered<T>>
	{
		size_t operator()(const Metered<T>& k) const
		{
			return std::hash<T>()(k.inner_value);
		}
	};
}
