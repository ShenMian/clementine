// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>
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
	static void isTrue(bool expr, const char*, const char*, unsigned int);
	static void isTrue(bool expr, const std::string_view& msg, const char*, const char*, unsigned int);

	static void isFalse(bool expr, const char*, const char*, unsigned int);
	static void isFalse(bool expr, const std::string_view& msg, const char*, const char*, unsigned int);

	static void isNotNull(void* ptr, const char*, const char*, unsigned int);
	static void isNotNull(void* ptr, const std::string_view& msg, const char*, const char*, unsigned int);
	template <typename T>
	static void isNotNull(std::shared_ptr<T>& ptr, const char*, const char*, unsigned int);

	static void isNull(void* ptr, const char*, const char*, unsigned int);
	static void isNull(void* ptr, const std::string_view& msg, const char*, const char*, unsigned int);
	template <typename T>
	static void isNull(std::shared_ptr<T>& ptr, const char*, const char*, unsigned int);
};

template <typename T>
inline void Assert::isNotNull(std::shared_ptr<T>& ptr, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr, file, line);
}

template <typename T>
inline void Assert::isNull(std::shared_ptr<T>& ptr, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr == nullptr, file, line);
}
} // namespace clem

#define CALL_INFO __FILE__, __FUNCTION__, __LINE__

#define CLEM_ASSERT_TRUE(expr, msg)    clem::Assert::isTrue(expr, msg, CALL_INFO);
#define CLEM_ASSERT_FALSE(expr, msg)   clem::Assert::isFalse(expr, msg, CALL_INFO);
#define CLEM_ASSERT_NULL(ptr, msg)     clem::Assert::isNull(ptr, msg, CALL_INFO);
#define CLEM_ASSERT_NOT_NULL(ptr, msg) clem::Assert::isNotNull(ptr, msg, CALL_INFO);
#define CLEM_ASSERT_EQ(val1, val2)     clem::Assert::isTrue((val1) == (val2), msg, CALL_INFO);
#define CLEM_ASSERT_NE(val1, val2)     clem::Assert::isTrue((val1) != (val2), msg, CALL_INFO);
