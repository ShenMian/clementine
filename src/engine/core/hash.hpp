// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <functional>

namespace core
{

template <typename T>
inline constexpr void hash_combine(std::size_t& seed, const T& v)
{
	seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T, typename... Ts>
inline constexpr void hash_combine(std::size_t& seed, const T& v, Ts... rest)
{
	hash_combine(seed, v);
	if constexpr(sizeof...(Ts) > 1)
		hash_combine(seed, rest...);
}

#define MAKE_HASHABLE(type, ...)                                                                                       \
	template <>                                                                                                        \
	struct std::hash<type>                                                                                             \
	{                                                                                                                  \
		std::size_t operator()(const type& t) const                                                                    \
		{                                                                                                              \
			std::size_t ret = 0;                                                                                       \
			hash_combine(ret, __VA_ARGS__);                                                                            \
			return ret;                                                                                                \
		}                                                                                                              \
	};

} // namespace core
