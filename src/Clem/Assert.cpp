// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.h"

using std::string;
using std::string_view;

void Assert::isTrue(bool expr, const char* file, unsigned int line)
{
	if(expr)
		return;

	printf("Assertion failed.\n"
				 "- file: %s\n"
				 "- line: %u\n",
				 file, line);
	breakpoint();
}

void Assert::isTrue(bool expr, const string_view& msg, const char* file, unsigned int line)
{
	if(expr)
		return;

	printf("Assertion failed.\n"
				 "- message: %s\n"
				 "- file:    %s\n"
				 "- line:    %u\n",
				 string(msg).c_str(), file, line);
	breakpoint();
}

void Assert::isFalse(bool expr, const char* file, unsigned int line)
{
	isTrue(!expr, file, line);
}

void Assert::isFalse(bool expr, const string_view& msg, const char* file, unsigned int line)
{
	isTrue(!expr, msg, file, line);
}

void Assert::isNotNull(void* expr, const char* file, unsigned int line)
{
	isTrue(expr != nullptr, file, line);
}

void Assert::isNotNull(void* expr, const std::string_view& msg, const char* file, unsigned int line)
{
	isTrue(expr != nullptr, msg, file, line);
}

void Assert::isNull(void* expr, const char* file, unsigned int line)
{
	isTrue(expr == nullptr, file, line);
}

void Assert::isNull(void* expr, const std::string_view& msg, const char* file, unsigned int line)
{
	isTrue(expr == nullptr, msg, file, line);
}
