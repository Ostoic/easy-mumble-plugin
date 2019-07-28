#include <iostream>
#include <functional>

#include "../../include/emp/plugin.hpp"

/**
 * This example shows that one can create a plugin using any kind of callable member.
 * emp::plugin uses CRTP to inspect the class' members to perform compile-time type
 * checks on the defined plugin.
 * Todo: MumblePlugin concept?
 */

void unlock_external()
{
	std::cout << "unlock external\n";
}

int trylock_external()
{
	std::cout << "trylock external\n";
	return 1;
}

class test_plugin : public emp::plugin<test_plugin>
{
public:
//member function:
	void about(void* arg)
	{
		std::cout << "test_plugin::about!\n";
	}

//static member function:
	static void config(void* arg)
	{
		std::cout << "test_plugin::config!\n";
	}

//static member variable pointer to function pointer:
	inline static auto trylock = trylock_external;

//member variable function pointer:
	using unlock_t = void(*)();
	unlock_t unlock = unlock_external;

	using trylock2_sig = emp::detail::member_functions::trylock2::signature;

//member variable callable object:
	std::function<trylock2_sig> trylock2 = [](const auto& map)
	{
		std::cout << "trylock2 via lambda!\n";
		return 2;
	};
};

int main()
{
	try
	{
		auto& plugin = test_plugin::create(L"Test Plugin");
		getMumblePlugin()->about(nullptr);
		std::cout << '\n';

		getMumblePlugin()->config(nullptr);
		std::cout << '\n';

		getMumblePlugin()->unlock();
		std::cout << '\n';

		getMumblePlugin()->trylock();
		std::cout << '\n';

		getMumblePlugin2()->trylock({});
	}
	catch (...)
	{

	}
	//test<test_plugin>();
	//about(nullptr);
	return 0;
}