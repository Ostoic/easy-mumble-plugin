#pragma once

#include "vector.hpp"

namespace emp::geometry
{
	class transformable
	{
	public:
		transformable() noexcept
			: position_{nullptr}
			, top_{nullptr}
			, front_{nullptr}
		{}

		explicit transformable(float* position, float* front, float* top) noexcept
			: position_{position}
			, front_{front}
			, top_{top}
		{}

		transformable& operator=(const transformable& other);

		bool empty() const noexcept;

		void height(float height) noexcept;
		float height() const noexcept;

		void top(const geometry::vector& top) noexcept;
		geometry::vector top() const noexcept;

		void front(const geometry::vector& front) noexcept;
		geometry::vector front() const noexcept;

		void position(const geometry::vector& position) noexcept;
		geometry::vector position() const noexcept;

		friend bool operator==(const transformable& lhs, const transformable& rhs);

	private:
		float* position_;
		float* front_;
		float* top_;
	};

	bool operator!=(const transformable& lhs, const transformable& rhs);
}

namespace emp::geometry
{
	bool operator==(const transformable& lhs, const transformable& rhs)
	{
		return std::equal(lhs.position_, &(lhs.position_[2]), rhs.position_) &&
			std::equal(lhs.front_, &(lhs.front_[2]), rhs.front_) &&
			std::equal(lhs.top_, &(lhs.top_[2]), rhs.top_);
	}

	bool operator!=(const transformable& lhs, const transformable& rhs)
	{
		return !operator==(lhs, rhs);
	}

	transformable& transformable::operator=(const transformable& other)
	{
		auto copy_array3 = [](const auto& lhs, auto& rhs)
		{
			for (int i = 0; i < 3; i++)
				rhs[i] = lhs[i];
		};

		copy_array3(other.position_, this->position_);
		copy_array3(other.front_, this->front_);
		copy_array3(other.top_, this->top_);
		return *this;
	}

	bool transformable::empty() const noexcept
	{
		return position_ == nullptr || front_ == nullptr || top_ == nullptr;
	}

	void transformable::height(const float height) noexcept
	{
		const auto pos = this->position();
		this->top({pos.x(), pos.y(), pos.z() + height});
	}

	float transformable::height() const noexcept
	{
		return geometry::distance(this->position(), this->top());
	}

	void transformable::top(const geometry::vector& top) noexcept
	{
		top_[0] = top[0];
		top_[1] = top[1];
		top_[2] = top[2];
	}

	geometry::vector transformable::top() const noexcept
	{
		return {top_[0], top_[1], top_[2]};
	}

	void transformable::front(const geometry::vector& front) noexcept
	{
		front_[0] = front[0];
		front_[1] = front[1];
		front_[2] = front[2];
	}

	geometry::vector transformable::front() const noexcept
	{
		return {front_[0], front_[1], front_[2]};
	}

	void transformable::position(const geometry::vector& position) noexcept
	{
		position_[0] = position[0];
		position_[1] = position[1];
		position_[2] = position[2];
	}

	geometry::vector transformable::position() const noexcept
	{
		return {position_[0], position_[1], position_[2]};
	}
}