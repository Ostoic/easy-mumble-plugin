#include <iostream>
#include <functional>
#include <array>

#include <distant/wow/entities/object_manager.hpp>

#include "../../include/emp/plugin.hpp"

class test_plugin : public emp::plugin<test_plugin>
{
public:
	static int lock()
	{

	}

	static bool fetch(emp::avatar& avatar, std::string& context, std::wstring& identity)
	{
		auto& me = distant::wow::local_player();

		avatar.position(me.position());
		return false;
	}

	//int trylock()
	//{
	//	std::cout << "hey\n";
	//	return 1;
	//}
private:
};

int main()
{
	try
	{
		auto avatar_pos = std::array{1.f, 2.f, 3.f};
		auto avatar_front = std::array{1.f, 2.f, 3.f};
		auto avatar_top = std::array{1.f, 2.f, 3.f};
		std::string context;
		std::wstring identity;

		auto avatar = emp::avatar{avatar_pos.data(), avatar_front.data(), avatar_top.data()};
		auto& plugin = test_plugin::create(L"Test Plugin");

		getMumblePlugin()->fetch(
			avatar_pos.data(), avatar_front.data(), avatar_top.data(),
			avatar_pos.data(), avatar_front.data(), avatar_top.data(),
			context, identity
		);
	}
	catch (...)
	{
	}
	return 0;
}