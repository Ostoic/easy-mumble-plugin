#pragma once

#include "type_traits.hpp"

#include <string_view>
#include <string>
#include <map>

#include "../avatar.hpp"
#include "../camera.hpp"

#ifndef NDEBUG
#	include <typeinfo>
#	include <iostream>
#endif

#define EMP_DETAIL_DEBUG_MEMBER_TYPE(member) std::cout << "typeid(" #member "): " << typeid(&Plugin::member).name() << '\n';

namespace emp::detail::member_functions
{
	//detection expression types
	struct about
	{
		template <class T>
		using detector = decltype(std::declval<T>().about(std::declval<void*>()));

		using signature = void(void*);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, void>;

		template <class Plugin>
		struct internal
		{
			static void adaptor(void* arg)
			{
				auto& plugin = Plugin::get();
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(about);
#endif
				plugin.about(arg);
			}
		};
	};

	struct config
	{
		template <class T>
		using detector = decltype(std::declval<T>().config(std::declval<void*>()));

		using signature = void(void*);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, void>;

		template <class Plugin>
		struct internal
		{
			static void adaptor(void* arg)
			{
				auto& plugin = Plugin::get();
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(config);
#endif
				plugin.config(arg);
			}
		};
	};

	struct trylock
	{
		template <class T>
		using detector = decltype(std::declval<T>().trylock());

		using signature = int();

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, int>;

		template <class Plugin>
		struct internal
		{
			static int adaptor()
			{
				auto& plugin = Plugin::get();
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(trylock);
#endif
				return plugin.trylock();
			}
		};
	};

	struct trylock2
	{
		template <class T>
		using detector = decltype(
			std::declval<T>().trylock2(
				std::declval<const std::multimap<std::wstring, unsigned long long int>&>()
			)
		);

		using signature = int(const std::multimap<std::wstring, unsigned long long int>&);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, int>;

		template <class Plugin>
		struct internal
		{
			static int adaptor(const std::multimap<std::wstring, unsigned long long int>& arg)
			{
				auto& plugin = Plugin::get();
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(trylock2);
#endif
				return plugin.trylock2(arg);
			}
		};
	};

	struct unlock
	{
		template <class T>
		using detector = decltype(std::declval<T>().unlock());

		using signature = void();

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, void>;

		template <class Plugin>
		struct internal
		{
			static void adaptor()
			{
				auto& plugin = Plugin::get();
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(unlock);
#endif
				plugin.unlock();
			}
		};
	};

	struct longdesc
	{
		template <class T>
		using detector = decltype(std::declval<T>().longdesc());

		using signature = std::wstring();

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, std::wstring>;

		template <class Plugin>
		struct internal
		{
			static std::wstring adaptor()
			{
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(longdesc);
#endif
				return Plugin::get().longdesc();
			}
		};
	};

	struct fetch
	{
		template <class T>
		using detector = decltype(std::declval<T>().fetch(
			std::declval<float*>(),
			std::declval<float*>(),
			std::declval<float*>(),
			std::declval<float*>(),
			std::declval<float*>(),
			std::declval<float*>(),
			std::declval<std::string&>(),
			std::declval<std::wstring&>()
		));

		using signature = int(
			float*,
			float*,
			float*,
			float*,
			float*,
			float*,
			std::string&,
			std::wstring&
		);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, int>;

		template <class Plugin>
		struct internal
		{
			static int adaptor(
				float* avatar_pos,
				float* avatar_front,
				float* avatar_top,
				float* camera_pos,
				float* camera_front,
				float* camera_top,
				std::string& context,
				std::wstring& identity)
			{
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(fetch);
#endif
				return Plugin::get().fetch(avatar_pos, avatar_front, avatar_top, camera_pos, camera_front, camera_top, context, identity);
			}
		};
	};

	struct fetch_ac
	{
		template <class T>
		using detector = decltype(std::declval<T>().fetch(
			std::declval<emp::avatar&>(),
			std::declval<emp::camera&>(),
			std::declval<std::string&>(),
			std::declval<std::wstring&>()
		));

		using signature = bool(
			emp::avatar&,
			emp::camera&,
			std::string&,
			std::wstring&
		);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, int>;

		template <class Plugin>
		struct internal
		{
			static int adaptor(
				float* avatar_pos,
				float* avatar_front,
				float* avatar_top,
				float* camera_pos,
				float* camera_front,
				float* camera_top,
				std::string& context,
				std::wstring& identity)
			{
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(fetch);
#endif
				auto avatar = emp::avatar{avatar_pos, avatar_front, avatar_top};
				auto camera = emp::camera{camera_pos, camera_front, camera_top};
				return Plugin::get().fetch(avatar, camera, context, identity);
			}
		};
	};

	struct fetch_a
	{
		template <class T>
		using detector = decltype(std::declval<T>().fetch(
			std::declval<emp::avatar&>(),
			std::declval<std::string&>(),
			std::declval<std::wstring&>()
		));

		using signature = bool(
			emp::avatar& avatar,
			std::string&,
			std::wstring&
		);

		template <class T>
		using exists_in = is_detected<detector, T>;

		template <class T>
		using valid_in = std::is_convertible<detector<T>, int>;

		template <class Plugin>
		struct internal
		{
			static int adaptor(
				float* avatar_pos,
				float* avatar_front,
				float* avatar_top,
				float* camera_pos,
				float* camera_front,
				float* camera_top,
				std::string& context,
				std::wstring& identity)
			{
#ifndef NDEBUG
				EMP_DETAIL_DEBUG_MEMBER_TYPE(fetch);
#endif
				auto avatar = emp::avatar{avatar_pos, avatar_front, avatar_top};
				auto camera = emp::camera{camera_pos, camera_front, camera_top};

				const auto result = Plugin::get().fetch(avatar, context, identity);
				camera = avatar;
				return result;
			}
		};
	};
}
