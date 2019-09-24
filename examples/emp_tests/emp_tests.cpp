#include "pch.h"
#include "CppUnitTest.h"
#include "test_plugin.hpp"

#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace emptests
{
	TEST_CLASS(emptests)
	{
	public:
		TEST_METHOD(basic_transformable)
		{
			auto avatar_pos = std::array{1.f, 1.f, 2.f};
			auto avatar_front = std::array{2.f, 1.f, 2.f};
			auto avatar_top = std::array{3.f, 1.f, 2.f};

			auto camera_pos = std::array{1.f, 1.f, 2.f};
			auto camera_front = std::array{2.f, 1.f, 2.f};
			auto camera_top = std::array{3.f, 1.f, 2.f};

			auto avatar = emp::avatar{avatar_pos.data(), avatar_front.data(), avatar_top.data()};
			auto camera = emp::camera{camera_pos.data(), camera_front.data(), camera_top.data()};

			Assert::IsTrue(avatar.position() == avatar_pos);
			Assert::IsTrue(avatar.front() == avatar_front);
			Assert::IsTrue(avatar.top() == avatar_top);

			Assert::IsTrue(camera.position() == camera_pos);
			Assert::IsTrue(camera.front() == camera_front);
			Assert::IsTrue(camera.top() == camera_top);

			Assert::IsTrue(avatar == camera);
			camera_top[0] = 0;

			Assert::IsTrue(avatar != camera);
		}

		TEST_METHOD(basic_plugin)
		{
			auto& plugin = test_plugin::create(L"Plugin");
			auto& identity = plugin.name();

			Assert::IsTrue(getMumblePlugin()->name == plugin.name());
			Assert::IsTrue(getMumblePlugin()->description == plugin.description());
			Assert::IsTrue(getMumblePlugin()->about != nullptr);
			Assert::IsTrue(getMumblePlugin()->config != nullptr);
			Assert::IsTrue(getMumblePlugin()->unlock != nullptr);
			Assert::IsTrue(getMumblePlugin2()->trylock != nullptr);
			Assert::IsTrue(getMumblePlugin()->fetch != nullptr);
			Assert::IsTrue(getMumblePlugin()->trylock != nullptr ||
				getMumblePlugin2()->trylock != nullptr
			);
		}

		TEST_METHOD(basic_fetch_a)
		{
			auto& plugin = test_plugin::create(L"Test Plugin");
			auto avatar_pos = std::array{1.f, 2.f, 3.f};
			auto avatar_front = std::array{1.f, 2.f, 3.f};
			auto avatar_top = std::array{1.f, 2.f, 3.f};
			auto camera_pos = std::array{1.f, 2.f, 3.f};
			auto camera_front = std::array{1.f, 2.f, 3.f};
			auto camera_top = std::array{1.f, 2.f, 3.f};
			auto avatar = emp::avatar{avatar_pos.data(), avatar_front.data(), avatar_top.data()};
			auto camera = emp::avatar{camera_pos.data(), camera_front.data(), camera_top.data()};

			std::string context;
			std::wstring identity;

			getMumblePlugin()->fetch(
				avatar_pos.data(), avatar_front.data(), avatar_top.data(),
				camera_pos.data(), camera_front.data(), camera_top.data(),
				context, identity
			);

			Assert::IsTrue(avatar == camera);
			Assert::IsTrue(avatar_pos[0] == 12326.2f);
			Assert::IsTrue(context == "context works!");
			Assert::IsTrue(identity == L"identity works!");
		}
	};
}
