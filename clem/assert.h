
#include <stdlib.h>
#include <stdio.h>

#define assert(expr, msg) \
	if(!(expr))             \
	{                       \
		fprintf("ASSERT: %s (%s %s:%d)", msg, __func__, __FILE__, __LINE__); \
		abort();              \
	}

