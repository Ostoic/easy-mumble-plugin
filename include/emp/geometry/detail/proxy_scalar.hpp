#pragma once

#include "../../detail/type_traits.hpp"

namespace emp::geometry::detail
{
	template <class Fn, class T>
	using accepts_type_t = decltype(std::declval<Fn>()(std::declval<T>()));

	template <class T, class Assignment>
	class proxy_object
	{
	public:
		static_assert(
			emp::detail::is_detected_v<accepts_type_t, Assignment, T>,
			"Assignment callable must accept T"
		);

		proxy_object(const Assignment& on_assign)
			: on_assign_{on_assign}
		{}

		proxy_object& operator=(const T& value) noexcept;
		operator float() const noexcept;

	private:
		const Assignment& on_assign_;
	};
}