// Copyright 2020 SMS
// License(Apache-2.0)
// 断言

#ifndef CLEM_ASSERT_H_
#define CLEM_ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG
#define assert(expr, msg)                                   \
	if(!(expr))                                               \
	{                                                         \
		fprintf(stderr,                                         \
						"Assertion '%s' failed: %s (%s %s:%d)",         \
						#expr, #msg, __FUNCTION__, __FILE__, __LINE__); \
		abort();                                                \
	}
#else
#define assert(expr, msg) ((void)0)
#endif // NDEBUG

#endif // !CLEM_ASSERT_H_
