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
	 * @param expression 要测试的表达式.
	 * @param message 提示消息.
	 * @param location 代码定位.
	 */
	static void isTrue(bool expression, std::string_view message, const std::source_location& location = std::source_location::current());

	/**
	 * @brief 断言.
	 * 表达式值为真时断言失败, 报告消息并结束程序.
	 *
	 * @param expression 要测试的表达式.
	 * @param message 提示消息.
	 * @param location 代码定位.
	 */
	static void isFalse(bool expression, std::string_view message, const std::source_location& location = std::source_location::current());
};

// 仅限影响性能的测试使用
#define CLEM_ASSERT(expression, message) Assert::isTrue(expression, message)

} // namespace clem