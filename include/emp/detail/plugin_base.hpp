#pragma once

#include "plugin_data.hpp"
#include "magic.hpp"

#include <string>
#include <functional>

namespace emp::detail
{
	class plugin_base
	{
	public:
		static constexpr unsigned int magic = EMP_PLUGIN_MAGIC;
		static constexpr unsigned int magic2 = EMP_PLUGIN_MAGIC_2;
		static constexpr unsigned int version = EMP_PLUGIN_VERSION;

		static plugin_base& get() noexcept;

	protected:
		plugin_base();

		explicit plugin_base(const std::wstring& name, const std::wstring& description);

	protected:
		std::wstring name_;
		std::wstring description_;
		plugin_data data_;
		plugin_data2 data2_;
	};

	plugin_data*& singleton_data()
	{
		static plugin_data* data = nullptr;
		return data;
	}

	plugin_data2*& singleton_data2()
	{
		static plugin_data2* data2 = nullptr;
		return data2;
	}
}

extern "C" EMP_PLUGIN_EXPORT emp::detail::plugin_data* getempPlugin();
extern "C" EMP_PLUGIN_EXPORT emp::detail::plugin_data2* getempPlugin2();

//implementation:
namespace emp::detail
{
	inline plugin_base::plugin_base()
		: plugin_base{L"", L""}
	{}

	inline plugin_base::plugin_base(const std::wstring& name, const std::wstring& description)
		: name_{name}
		, description_{description}
		, data_{
			plugin_base::magic,
			description_,
			name_,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		}
		, data2_{
			plugin_base::magic2,
			plugin_base::version,
			nullptr
		}
	{}

	inline plugin_base& plugin_base::get() noexcept
	{
		static plugin_base singleton;
		return singleton;
	}
}

extern "C" EMP_PLUGIN_EXPORT
	inline emp::detail::plugin_data* getempPlugin()
{
	return emp::detail::singleton_data();
}

extern "C" EMP_PLUGIN_EXPORT
	inline emp::detail::plugin_data2* getempPlugin2()
{
	return emp::detail::singleton_data2();
}