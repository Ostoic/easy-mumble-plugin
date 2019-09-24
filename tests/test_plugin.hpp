#pragma once
#include "CppUnitTest.h"
#include "..\include\emp.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace emptests
{
	void unlock_external()
	{
	}

	int trylock_external()
	{
		return 1;
	}

	class test_plugin : public emp::plugin<test_plugin>
	{
	public:
		void about(void* arg)
		{
		}

		static void config(void* arg)
		{
		}

		inline static auto trylock = trylock_external;

		using unlock_t = void(*)();
		unlock_t unlock = unlock_external;

		using trylock2_sig = emp::detail::member_functions::trylock2::signature;

		//member variable callable object:
		std::function<trylock2_sig> trylock2 = [](const auto& map)
		{
			Assert::IsTrue(!map.empty());
			return 2;
		};

		static bool fetch(emp::avatar& avatar, std::string& context, std::wstring& identity)
		{
			context = "context works!";
			identity = L"identity works!";
			avatar.position({12326.2f, 0.f, 0.f});
			Assert::IsTrue(!avatar.empty());
			Assert::IsTrue(!context.empty());
			Assert::IsTrue(!identity.empty());
			return true;
		}
	};

}