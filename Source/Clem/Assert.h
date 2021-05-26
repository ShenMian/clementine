﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <string>

#if _MSC_VER
#	define breakpoint() __debugbreak()
#else
#	define breakpoint() __buildin_trap()
#endif

namespace clem
{
/**
 * @brief 断言.
 *
 * Assert.method(expr, [msg,] CALL_INFO);
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

	/*
	template <typename T>
	static void isNull(const std::shared_ptr<T>& expr, ...);
	*/
};
} // namespace clem

#define CALL_INFO __FILE__, __LINE__

#define CLEM_ASSERT_TRUE(expr, msg)     clem::Assert::isTrue(expr, msg, CALL_INFO);
#define CLEM_ASSERT_FALSE(expr, msg)    clem::Assert::isFalse(expr, msg, CALL_INFO);
#define CLEM_ASSERT_NULL(expr, msg)     clem::Assert::isNull(expr, msg, CALL_INFO);
#define CLEM_ASSERT_NOT_NULL(expr, msg) clem::Assert::isNotNull(expr, msg, CALL_INFO);
#define CLEM_ASSERT_EQ(val1, val2)      clem::Assert::isTrue((val1) == (val2), msg, CALL_INFO);
#define CLEM_ASSERT_NE(val1, val2)      clem::Assert::isTrue((val1) != (val2), msg, CALL_INFO);