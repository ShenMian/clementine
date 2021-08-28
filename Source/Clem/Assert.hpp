// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <format>
#include <source_location>
#include <string_view>

namespace clem
{

class Assert
{
public:
    /**
	 * @brief 断言.
	 * 表达式值为假时断言失败, 报告消息并结束程序.
	 *
	 * @param expr 要测试的表达式.
	 * @param msg  提示消息.
	 * @param loc  代码定位.
	 */
    static void isTrue(bool expr, std::string_view msg = "", const std::source_location& loc = std::source_location::current());

    /**
	 * @brief 断言.
	 * 表达式值为真时断言失败, 报告消息并结束程序.
	 *
	 * @param expr 要测试的表达式.
	 * @param msg  提示消息.
	 * @param loc  代码定位.
	 */
    static void isFalse(bool expr, std::string_view msg = "", const std::source_location& loc = std::source_location::current());
};

// 仅限影响性能的测试使用
#if 1
#    define CLEM_ASSERT(expr, msg) Assert::isTrue(expr, msg)
#else
#    define CLEM_ASSERT(expr, msg)
#endif

} // namespace clem