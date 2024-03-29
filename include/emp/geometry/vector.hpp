#pragma once

#include <array>
#include <cmath>

namespace emp::geometry
{
	class vector : public std::array<float, 3>
	{
	public:
		constexpr vector(const float x = 0, const float y = 0, const float z = 0) noexcept;

		template <std::size_t N>
		constexpr vector(const std::array<float, N>& array) noexcept;

		template <std::size_t N>
		operator std::array<float, N>() noexcept;

		constexpr float x() const noexcept;
		constexpr float& x() noexcept;

		constexpr float y() const noexcept;
		constexpr float& y() noexcept;

		constexpr float z() const noexcept;
		constexpr float& z() noexcept;

		vector& shift(float value) noexcept;

		void normalize() noexcept;
		float magnitude() const noexcept;
		constexpr float magnitude_squared() const noexcept;

		constexpr vector& operator-() noexcept;

	private:
		using base = std::array<float, 3>;
	};

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept;
	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept;

	template <class Scalar, class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
	constexpr vector operator*(const Scalar scalar, const vector& rhs) noexcept;

	template <class Scalar, class = std::enable_if_t<std::is_scalar_v<Scalar>>>
	constexpr vector operator*(const vector& lhs, const Scalar scalar) noexcept;

	constexpr float magnitude_squared(const vector & vector) noexcept;

	float magnitude(const vector& vector) noexcept;

	float length(const vector& vector) noexcept;

	void normalize(vector& vector) noexcept;

	constexpr float distance_squared(const vector& lhs, const vector& rhs) noexcept;

	float distance(const vector & lhs, const vector & rhs);
}

namespace emp::geometry
{
	constexpr vector::vector(const float x, const float y, const float z) noexcept
		: vector::base{x, y, z}
	{}

	template <std::size_t N>
	constexpr vector::vector(const std::array<float, N>& array) noexcept
		: vector::base{array[0], array[1], array[2]}
	{}

	template <std::size_t N>
	vector::operator std::array<float, N>() noexcept
	{
		static_assert(N >= 3);
		return std::array{x(), y(), z()};
	}

	constexpr float vector::x() const noexcept
	{
		return (*this)[0];
	}

	constexpr float& vector::x() noexcept
	{
		return (*this)[0];
	}

	constexpr float vector::y() const noexcept
	{
		return (*this)[1];
	}

	constexpr float& vector::y() noexcept
	{
		return (*this)[1];
	}

	constexpr float vector::z() const noexcept
	{
		return (*this)[2];
	}

	constexpr float& vector::z() noexcept
	{
		return (*this)[2];
	}

	vector& vector::shift(const float value) noexcept
	{
		(*this)[0] += value;
		(*this)[1] += value;
		(*this)[2] += value;
		return *this;
	}

	void vector::normalize() noexcept
	{
		const auto m = this->magnitude();
		x() /= m;
		y() /= m;
		z() /= m;
	}

	float vector::magnitude() const noexcept
	{
		return std::sqrt(this->magnitude_squared());
	}

	constexpr vector& vector::operator-() noexcept
	{
		(*this) = vector{} - *this;
		return *this;
	}

	template <class Scalar, class>
	constexpr vector operator*(const Scalar scalar, const vector& rhs) noexcept
	{
		return {scalar * rhs.x(), scalar * rhs.y(), scalar * rhs.z()};
	}

	template <class Scalar, class>
	constexpr vector operator*(const vector& lhs, const Scalar scalar) noexcept
	{
		return {scalar * lhs.x(), scalar * lhs.y(), scalar * lhs.z()};
	}

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept
	{
		return vector{
			lhs.x() + rhs.x(),
			lhs.y() + rhs.y(),
			lhs.z() + rhs.z()
		};
	}

	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept
	{
		return vector{
			lhs.x() - rhs.x(),
			lhs.y() - rhs.y(),
			lhs.z() - rhs.z()
		};
	}

	constexpr float vector::magnitude_squared() const noexcept
	{
		return x() * x() + y() * y() + z() * z();
	}

	constexpr float magnitude_squared(const vector& vector) noexcept
	{
		return vector.magnitude_squared();
	}

	float magnitude(const vector& vector) noexcept
	{
		return vector.magnitude();
	}

	float length(const vector& vector) noexcept
	{
		return magnitude(vector);
	}

	void normalize(vector& vector) noexcept
	{
		vector.normalize();
	}

	constexpr float distance_squared(const vector& lhs, const vector& rhs) noexcept
	{
		return magnitude_squared(lhs - rhs);
	}

	float distance(const vector& lhs, const vector& rhs)
	{
		return std::sqrt(distance_squared(lhs, rhs));
	}
}