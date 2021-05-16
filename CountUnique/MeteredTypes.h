#pragma once

#include "MetricsCounter.h"

template <class T>
class Metered final
{
public:
	using This = Metered<T>;

public:
	template <class ... Args>
	Metered(Args ...args) : inner_value(args...)
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
		return inner_value == other.inner_value;
	}

	bool operator==(T other) const
	{
		MetricsCounter::add_comparison();
		return inner_value == other;
	}

	bool operator!=(This other) const
	{
		MetricsCounter::add_comparison();
		return inner_value != other.inner_value;
	}

	bool operator>=(This other) const
	{
		MetricsCounter::add_comparison();
		return inner_value >= other.inner_value;
	}

	bool operator>(This other) const
	{
		MetricsCounter::add_comparison();
		return inner_value > other.inner_value;
	}

	bool operator<=(This other) const
	{
		MetricsCounter::add_comparison();
		return inner_value <= other.inner_value;
	}

	bool operator<(This other) const
	{
		MetricsCounter::add_comparison();
		return inner_value < other.inner_value;
	}

	This& operator=(This other)
	{
		MetricsCounter::add_placement();
		inner_value = other.inner_value;
		return *this;
	}

	T operator++(int)
	{
		MetricsCounter::add_placement();
		T temp = inner_value;
		inner_value++;
		return temp;
	}

	This& operator++()
	{
		MetricsCounter::add_placement();
		inner_value++;
		return *this;
	}

	T operator--(int)
	{
		MetricsCounter::add_placement();
		T temp = value;
		inner_value--;
		return temp;
	}

	This& operator--()
	{
		MetricsCounter::add_placement();
		inner_value--;
		return *this;
	}

	operator const T&() const
	{
		return inner_value;
	}
	
	T value()
	{
		static_assert(std::is_trivial_v<T>, "Can only get a copy for trivial types");
		return inner_value;
	}

private:
	T inner_value;
};
