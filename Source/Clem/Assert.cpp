// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.h"
#include "Logger.h"
#include "Platform.h"
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

	auto str = std::format("Assertion failed.\nfile    : {}\nfunction: {}\nline    : {}\n", loc.file_name(), loc.function_name(), loc.line());
    if(!msg.empty())
      str += std::format("message : {}", msg);

	std::cout << str << std::endl;

	#ifdef OS_WIN
    MessageBoxA(nullptr, str.c_str(), "Clementine", 0);
	#endif

	breakpoint();
}

void Assert::isFalse(bool expr, std::string_view msg, const std::source_location& loc)
{
	isTrue(!expr, msg, loc);
}

} // namespace clem