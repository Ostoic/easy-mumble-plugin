#pragma once

namespace emp::geometry
{
	constexpr int factorial(const unsigned int n) noexcept
	{
		unsigned int result = 1;
		for (unsigned int i = n; i > 0; i--)
			result *= i;

		return result;
	}

	constexpr float sqrt(const float x) noexcept
	{

	}
}