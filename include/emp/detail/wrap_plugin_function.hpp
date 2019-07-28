#pragma once

#include "plugin_traits.hpp"

namespace emp::detail
{
	template <class ErrorType>
	void see_this_member_function() = delete;

	template <class Plugin, class Member, class empFn>
	void wrap_plugin_function(empFn& fn_ptr)
	{
		if constexpr (plugin_traits<Plugin>::template has<Member>)
		{
			if constexpr (!plugin_traits<Plugin>::template valid<Member>)
			{
				see_this_member_function<Member>();
				static_assert(false, "[emp::plugin] Your plugin's member function has the wrong return type (see template instantiation for details)");
			}

			fn_ptr = plugin_traits<Plugin>::template internal<Member>::wrapper;
		}

		else
			fn_ptr = nullptr;
	}
}