// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdio>
#include <exception>
#include <string_view>
// #include <source_location>
// TODO: 等待 apple-clang 支持 std::source_location.

namespace core
{

inline void breakpoint()
{
#if _MSC_VER
	__debugbreak();
#else
	__builtin_trap();
#endif
}

[[noreturn]] inline void unreachable()
{
#if _MSC_VER
	__assume(false);
#else
	__builtin_unreachable();
#endif
}

/**
 * @brief 断言.
 *
 * @param cond 条件.
 */
template <typename T>
constexpr void check(T&& cond)
{
	if(cond)
		return;

	breakpoint(); // debug
	              // terminate(); // release
}

/**
 * @brief 断言.
 *
 * @param cond 条件.
 * @param msg  描述.
 */
template <typename T>
constexpr void check(T&& cond, std::string_view msg)
{
	if(cond)
		return;

	std::puts(msg.data());
	breakpoint(); // debug
	              // terminate(); // release
}

/**
 * @brief 断言.
 *
 * @param cond 条件.
 */
/*
inline void check(bool cond, const std::source_location& loc = std::source_location::current())
{
    if(cond)
        return;

    std::printf("Assertion failed %s:%s(%u:%u)\n", loc.file_name(), loc.function_name(), loc.line(), loc.column());
    breakpoint(); // debug
    // terminate(); // release
}
*/

/**
 * @brief 断言.
 *
 * @param cond 条件.
 * @param msg  描述.
 */
/*
inline void check(bool cond, std::string_view msg,
                  const std::source_location& loc = std::source_location::current())
{
    if(cond)
        return;

    std::printf("Assertion failed %s:%s(%u:%u): %s\n", loc.file_name(), loc.function_name(), loc.line(), loc.column(),
                msg.data());
    breakpoint(); // debug
    // terminate(); // release
}
*/

#define ENABLE_CHECK !NDEBUG

#if ENABLE_CHECK

	#define debug_check(...) ::core::check(__VA_ARGS__)

#else

	#define debug_check(...) (static_cast<void>(0))

#endif

} // namespace core
