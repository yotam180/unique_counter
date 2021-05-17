#pragma once

#include "MetricsCounter.h"

template <class T>
class Metered final
{
public:
	using This = Metered<T>;

public:
	template <class ... Args>
	Metered(Args ...args) noexcept : inner_value(args...)
	{
		// We count a construction of a metered object as a placement to count the initial array initialization, etc.
		// Otherwise, algorithms that require dynamic allocations will not be metered correctly
		// (since the new allocations would appear as 0 placements)
		MetricsCounter::add_placement();
	}

public:
	bool operator==(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value == other.inner_value;
	}

	bool operator==(T other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value == other;
	}

	bool operator!=(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value != other.inner_value;
	}

	bool operator>=(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value >= other.inner_value;
	}

	bool operator>(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value > other.inner_value;
	}

	bool operator<=(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value <= other.inner_value;
	}

	bool operator<(This other) const noexcept
	{
		MetricsCounter::add_comparison();
		return inner_value < other.inner_value;
	}

	This& operator=(This other) noexcept
	{
		MetricsCounter::add_placement();
		inner_value = other.inner_value;
		return *this;
	}

	T operator++(int) noexcept
	{
		MetricsCounter::add_placement();
		T temp = inner_value;
		inner_value++;
		return temp;
	}

	This& operator++() noexcept
	{
		MetricsCounter::add_placement();
		inner_value++;
		return *this;
	}

	T operator--(int) noexcept
	{
		MetricsCounter::add_placement();
		T temp = value;
		inner_value--;
		return temp;
	}

	This& operator--() noexcept
	{
		MetricsCounter::add_placement();
		inner_value--;
		return *this;
	}

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

public:
	struct hash
	{
		std::size_t operator()(const Metered<T>& k) const
		{
			return std::hash<T>()(k.inner_value);
		}
	};
};