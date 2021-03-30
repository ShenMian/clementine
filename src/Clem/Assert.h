// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#if _MSC_VER
#	define breakpoint() __debugbreak()
#else
#	define breakpoint() __buildin_trap()
#endif

#define assert(expr, msg) \
	if(!(expr))             \
	{                       \
		breakpoint();         \
	}
