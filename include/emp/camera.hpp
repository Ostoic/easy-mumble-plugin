#pragma once

#include "geometry/transformable.hpp"

namespace emp
{
	class camera : public geometry::transformable
	{
	public:
		camera() noexcept = default;

		explicit camera(float* position, float* front, float* top) noexcept
			: geometry::transformable{position, front, top}
		{}

		camera& operator=(const transformable& other)
		{
			static_cast<transformable&>(*this) = other;
			return *this;
		}
	};
}