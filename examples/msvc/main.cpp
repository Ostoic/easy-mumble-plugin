#include <iostream>
#include <functional>
#include <array>

#include "../../include/emp/plugin.hpp"

#include <WS2tcpip.h>

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

//static member variable function pointer:
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

	//inline static const auto& fetch = std::function{[](
	//	float* avatar_pos, float* avatar_front, float* avatar_top,
	//	float* camera_pos, float* camera_front, float* camera_top,
	//	std::string& context, std::wstring& identity)
	//{
	//	return true;
	//}};

	static bool fetch(emp::avatar& avatar, std::string& context, std::wstring& identity)
	{
		avatar.position({avatar.position().x() + 10, 0, 0});

		context = "hey there";
		identity = L"HELLO";
		std::cerr << "test_plugin::fetch called!\n";
		return false;
	}

	// hmm how do we handle this
	//bool fetch(
	//	std::array<float, 3>& avatar,
	//	std::array<float, 3>& camera,
	//	std::string& context, std::wstring& identity)
	//{
	//	return true;
	//}

	//template <class Avatar, class Camera>
	//int fetch()
};

/*
** Use library types (camera, avatar, etc) types to choose which fetch function to adapt
** default will be:
**	bool fetch(emp::avatar& avatar, emp::camera& camera, context, identity)
** If we detect a fetch with only the avatar, then we make the camera be
** the same as the avatar
**
*/

int main()
{
	try
	{
		// emp::plugin allows you to use any generic callable object with the exported
		// Mumble plugin data. Normally
		auto& plugin = test_plugin::create(L"Test Plugin");
		test_plugin::magic;

		getMumblePlugin()->about(nullptr);
		std::cout << '\n';

		getMumblePlugin()->config(nullptr);
		std::cout << '\n';

		getMumblePlugin()->unlock();
		std::cout << '\n';

		getMumblePlugin()->trylock();
		std::cout << '\n';

		getMumblePlugin2()->trylock({});
		std::cout << '\n';

		std::string context;
		std::wstring identity;

		auto avatar_pos = std::array{1.f, 1.f, 2.f};
		auto avatar_front = std::array{2.f, 1.f, 2.f};
		auto avatar_top = std::array{3.f, 1.f, 2.f};
		auto camera_pos = std::array{4.f, 1.f, 2.f};
		auto camera_front = std::array{5.f, 1.f, 2.f};
		auto camera_top = std::array{6.f, 1.f, 2.f};

		getMumblePlugin()->fetch(
			avatar_pos.data(), avatar_front.data(), avatar_top.data(),
			camera_pos.data(), camera_front.data(), camera_top.data(),
			context, identity
		);
	}
	catch (...)
	{
	}
	//test<test_plugin>();
	//about(nullptr);
	return 0;
}