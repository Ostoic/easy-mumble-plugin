// Copyright 2005-2019 The emp Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// emp source tree or at <https://www.emp.info/LICENSE>.

#pragma once

#include <string>
#include <map>

#include "type_traits.hpp"

namespace emp::detail
{
	struct plugin_data
	{
		unsigned int magic;
		const std::wstring& description;
		const std::wstring& name;

		fn_ptr<void(void*)> about;
		fn_ptr<void(void*)> config;
		fn_ptr<int()> trylock;
		fn_ptr<void()> unlock;
		fn_ptr<std::wstring()> longdesc;
		fn_ptr<int(float*, float*, float*, float*, float*, float*, std::string&, std::wstring&)> fetch;
	};

	struct plugin_data2
	{
		unsigned int magic;
		unsigned int version;
		fn_ptr<int(const std::multimap<std::wstring, unsigned long long int>&)> trylock;
	};
}
