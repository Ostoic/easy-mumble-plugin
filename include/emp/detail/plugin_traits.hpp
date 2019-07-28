#pragma once

namespace emp::detail
{
	template <class Plugin>
	struct plugin_traits
	{
		template <class Member>
		using has_t = typename Member::template exists_in<Plugin>;

		template <class Member>
		inline static constexpr bool has = has_t<Member>::value;

		template <class Member>
		using valid_t = typename Member::template valid_in<Plugin>;

		template <class Member>
		inline static constexpr bool valid = valid_t<Member>::value;

		template <class Member>
		using internal = typename Member::template internal<Plugin>;
	};
}