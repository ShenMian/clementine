// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include "platform.h"
#include <cstdio>
#include <string_view>
#include <type_traits>
// #include <source_location>

#if TARGET_COMPILER == COMPILER_MSVC
	#define breakpoint() __debugbreak()
#else
	#define breakpoint() __builtin_trap()
#endif

inline constexpr void check(bool condition)
{
	if(condition)
		return;
	breakpoint();
}

inline constexpr void check(bool condition, std::string_view message)
{
	if(condition)
		return;
	std::puts(message.data());
	breakpoint();
}

// TODO: clang 暂时不支持 std::source_location.
/*
inline void check(bool condition, const std::source_location& loc =
std::source_location::current())
{
        if(condition)
                return;

        std::printf("Assertion failed %s:%s(%u:%u)\n",
                loc.file_name(), loc.function_name(), loc.line(), loc.column());
        breakpoint();
}

inline void check(bool condition, std::string_view message, const
std::source_location& loc = std::source_location::current())
{
        if(condition)
                return;

        std::printf("Assertion failed %s:%s(%u:%u): %s\n",
                loc.file_name(), loc.function_name(), loc.line(), loc.column(),
message.data()); breakpoint();
}
*/
