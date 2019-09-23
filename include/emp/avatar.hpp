#pragma once

#include "geometry/transformable.hpp"

namespace emp
{
	class avatar : public geometry::transformable
	{
	public:
		avatar() noexcept = default;

		explicit avatar(float* position, float* front, float* top) noexcept
			: geometry::transformable{position, front, top}
		{}

		avatar& operator=(const transformable& other)
		{
			static_cast<transformable&>(*this) = other;
			return *this;
		}
	};
}