// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <string>

#if _MSC_VER
#	define breakpoint() __debugbreak()
#else
#	define breakpoint() __buildin_trap()
#endif

#define CALL_INFO __FILE__, __LINE__

namespace clem
{
/**
 * @brief 断言.
 *
 * @code Assert.method(expr, CALL_INFO);
 */
class Assert
{
public:
	static void isTrue(bool expr, const char*, unsigned int);
	static void isTrue(bool expr, const std::string_view& msg, const char*, unsigned int);

	static void isFalse(bool expr, const char*, unsigned int);
	static void isFalse(bool expr, const std::string_view& msg, const char*, unsigned int);

	static void isNotNull(void* expr, const char*, unsigned int);
	static void isNotNull(void* expr, const std::string_view& msg, const char*, unsigned int);

	static void isNull(void* expr, const char*, unsigned int);
	static void isNull(void* expr, const std::string_view& msg, const char*, unsigned int);

	Assert() = delete;
};
} // namespace clem
