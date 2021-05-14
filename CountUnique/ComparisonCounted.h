#pragma once

#include "ComparisonCounter.h"

template <class T>
class ComparisonCounted final
{
public:
	using This = ComparisonCounted<T>;

public:
	template <class ... Args>
	ComparisonCounted(Args ...args) : value(args...) {}

public:
	bool operator==(This other)
	{
		ComparisonCounter::add_comparison();
		return value == other.value;
	}

	bool operator>=(This other)
	{
		ComparisonCounter::add_comparison();
		return value >= other.value;
	}

	bool operator>(This other)
	{
		ComparisonCounter::add_comparison();
		return value > other.value;
	}

	bool operator<=(This other)
	{
		ComparisonCounter::add_comparison();
		return value <= other.value;
	}

	bool operator<(This other)
	{
		ComparisonCounter::add_comparison();
		return value < other.value;
	}

private:
	T value;
};
