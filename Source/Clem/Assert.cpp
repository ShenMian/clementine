// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.h"
#include "Logger.h"
#include <iostream>

#if _MSC_VER
#	define breakpoint() __debugbreak()
#else
#	define breakpoint() __builtin_trap()
#endif

namespace clem
{

void Assert::isTrue(bool expr, std::string_view msg, const std::source_location& loc)
{
	if(expr)
		return;

	std::cout << "Assertion failed." << std::endl;
	std::cout << "file    : " << loc.file_name() << std::endl;
	std::cout << "function: " << loc.function_name() << std::endl;
	std::cout << "line    : " << loc.line() << std::endl;

	breakpoint();
}

void Assert::isFalse(bool expr, std::string_view msg, const std::source_location& loc)
{
	isTrue(!expr, msg, loc);
}

} // namespace clem