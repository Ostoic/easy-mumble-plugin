#pragma once

#include "detail/member_functions.hpp"
#include "detail/plugin_traits.hpp"
#include "detail/plugin_base.hpp"
#include "detail/wrap_plugin_function.hpp"

namespace emp
{
	template <class Plugin>
	class plugin : public detail::plugin_base
	{
	public:
		static Plugin& get() noexcept;

		static Plugin& create(const std::wstring& name, const std::wstring& description = L"");

	public:
		[[nodiscard]] const std::wstring& name() const noexcept;

		[[nodiscard]] const std::wstring& description() const noexcept;

		void name(const std::wstring& name);
		void description(const std::wstring& name);

	protected:
		plugin() = default;

	private:
		static constexpr void check_plugin_support() noexcept;
	};

//implementation:
	template <class Plugin>
	[[nodiscard]] const std::wstring& plugin<Plugin>::name() const noexcept
	{
		return name_;
	}

	template <class Plugin>
	[[nodiscard]] const std::wstring& plugin<Plugin>::description() const noexcept
	{
		return description_;
	}

	template <class Plugin>
	void plugin<Plugin>::name(const std::wstring& name)
	{
		name_ = name;
	}

	template <class Plugin>
	void plugin<Plugin>::description(const std::wstring& name)
	{
		description_ = name;
	}

	template <class Plugin>
	Plugin& plugin<Plugin>::get() noexcept
	{
		plugin::check_plugin_support();
		static Plugin plugin;
		return plugin;
	}

	template <class Plugin>
	Plugin& plugin<Plugin>::create(const std::wstring& name, const std::wstring& description)
	{
		plugin::check_plugin_support();
		auto& p = static_cast<plugin&>(plugin::get());

		// Connect non-template data so getempPlugin can access it
		detail::singleton_data() = &p.data_;
		detail::singleton_data2() = &p.data2_;

		// Generate	appropriate member function wrappers
		detail::wrap_plugin_function<Plugin, detail::member_functions::about>(
			p.data_.about
		);

		detail::wrap_plugin_function<Plugin, detail::member_functions::config>(
			p.data_.config
		);

		detail::wrap_plugin_function<Plugin, detail::member_functions::trylock>(
			p.data_.trylock
		);

		detail::wrap_plugin_function<Plugin, detail::member_functions::trylock2>(
			p.data2_.trylock
		);

		detail::wrap_plugin_function<Plugin, detail::member_functions::unlock>(
			p.data_.unlock
		);

		detail::wrap_plugin_function<Plugin, detail::member_functions::fetch>(
			p.data_.fetch
		);

		// Set plugin name and description
		p.name_ = name;
		p.description_ = description;

		// Return a reference to the plugin singleton
		return plugin::get();
	}

	template <class Plugin>
	constexpr void plugin<Plugin>::check_plugin_support() noexcept
	{
		using namespace detail;

		static_assert(
			std::is_convertible_v<Plugin, plugin<Plugin>>,
			"[emp::plugin] Your plugin must be a type that is convertible to emp::plugin"
		);

		static_assert(
			std::is_default_constructible_v<Plugin>,
			"[emp::plugin] Your plugin must be default constructible"
		);

		constexpr auto fetch_exists = member_functions::fetch::exists_in<Plugin>::value;
		constexpr auto trylock_exists = member_functions::trylock::exists_in<Plugin>::value;

		//if constexpr (fetch_exists)
		//{
		//	static_assert(
		//		member_functions::fetch::valid_in<Plugin>::value,
		//		"[emp::plugin] Your plugin's fetch member function has the wrong return type"
		//	);
		//}
		//else
		//	static_assert(false, "[emp::plugin] Your plugin must provide a matching fetch member function");

		if constexpr (trylock_exists)
		{
			static_assert(
				plugin_traits<Plugin>::template valid<member_functions::trylock>,
				//member_functions::trylock::valid_in<Plugin>::value,
				"[emp::plugin] Your plugin's trylock member function has the wrong return type"
			);
		}
		else
			static_assert(false, "[emp::plugin] Your plugin must provide a matching trylock member function");
	}
}