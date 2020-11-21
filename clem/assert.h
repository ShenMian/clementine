// Copyright 2020 SMS
// License(Apache-2.0)
// ╤оят

#ifndef CLEM_ASSERT_H_
#define CLEM_ASSERT_H_

#include <stdlib.h>
#include <stdio.h>

#ifndef NDEBUG
#define assert(expr, msg)                                 \
	if(!(expr))                                             \
	{                                                       \
		fprintf(stderr,                                       \
			"\x1b[31m[-]\x1b[0m "                               \
			"Assertion '" #expr "' failed: " #msg " ("__FUNCTION__" " " " __FILE__ ":" __LINE__ ")"); \                  \
		abort();                                              \
	}
#else
#define assert(expr, msg) ((void)0)
#endif // NDEBUG

#endif // CLEM_ASSERT_H_
