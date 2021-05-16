#pragma once

#include "MetricsCounter.h"

template <class T>
class Metered final
{
public:
	using This = Metered<T>;

public:
	template <class ... Args>
	Metered(Args ...args) : value(args...)
	{
		// We count a construction of a metered object as a placement to count the initial array initialization, etc.
		// Otherwise, algorithms that require dynamic allocations will not be metered correctly
		// (since the new allocations would appear as 0 placements)
		MetricsCounter::add_placement();
	}

public:
	bool operator==(This other) const
	{
		MetricsCounter::add_comparison();
		return value == other.value;
	}

	bool operator!=(This other) const
	{
		MetricsCounter::add_comparison();
		return value != other.value;
	}

	bool operator>=(This other) const
	{
		MetricsCounter::add_comparison();
		return value >= other.value;
	}

	bool operator>(This other) const
	{
		MetricsCounter::add_comparison();
		return value > other.value;
	}

	bool operator<=(This other) const
	{
		MetricsCounter::add_comparison();
		return value <= other.value;
	}

	bool operator<(This other) const
	{
		MetricsCounter::add_comparison();
		return value < other.value;
	}

	This& operator=(This other)
	{
		MetricsCounter::add_placement();
		value = other.value;
		return *this;
	}

	operator T&()
	{
		return value;
	}

private:
	T value;
};
