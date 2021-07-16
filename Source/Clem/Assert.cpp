// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.h"
#include "Logger.h"

using std::string;
using std::string_view;

namespace clem
{
void Assert::isTrue(bool expr, const char* file, const char* func, unsigned int line)
{
	if(expr)
		return;

	printf("Assertion failed.\n"
				 "- file: %s\n"
				 "- func: %s\n"
				 "- line: %u\n",
				 file, func, line);
	// breakpoint();
	CLEM_LOG_FATAL("assert", "Assertion failed: file: {}, line: {}", file, line);
}

void Assert::isTrue(bool expr, const string_view& msg, const char* file, const char* func, unsigned int line)
{
	if(expr)
		return;

	printf("Assertion failed.\n"
				 "- message: %s\n"
				 "- file:    %s\n"
				 "- func:    %s\n"
				 "- line:    %u\n",
				 string(msg).c_str(), file, func, line);
	// breakpoint();
	CLEM_LOG_FATAL("assert", "Assertion failed: message: '{}', file: {}, line: {}", msg, file, line);
}

void Assert::isFalse(bool expr, const char* file, const char* func, unsigned int line)
{
	isTrue(!expr, file, func, line);
}

void Assert::isFalse(bool expr, const string_view& msg, const char* file, const char* func, unsigned int line)
{
	isTrue(!expr, msg, file, func, line);
}

void Assert::isNotNull(void* ptr, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr != nullptr, file, func, line);
}

void Assert::isNotNull(void* ptr, const std::string_view& msg, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr != nullptr, msg, file, func, line);
}

void Assert::isNull(void* ptr, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr == nullptr, file, func, line);
}

void Assert::isNull(void* ptr, const std::string_view& msg, const char* file, const char* func, unsigned int line)
{
	isTrue(ptr == nullptr, msg, file, func, line);
}
} // namespace clem