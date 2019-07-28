#include <iostream>
#include <functional>

#include "../../include/emp/plugin.hpp"

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
		getempPlugin()->about(nullptr);
		std::cout << '\n';

		getempPlugin()->config(nullptr);
		std::cout << '\n';

		getempPlugin()->unlock();
		std::cout << '\n';

		getempPlugin()->trylock();
		std::cout << '\n';

		getempPlugin2()->trylock({});
	}
	catch (...)
	{

	}
	//test<test_plugin>();
	//about(nullptr);
	return 0;
}