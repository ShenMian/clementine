// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

void ALCheckError();
void ALClearError();

#if 1
	#define ALCall(func)                                                                                               \
		do                                                                                                             \
		{                                                                                                              \
			ALClearError();                                                                                            \
			func;                                                                                                      \
			ALCheckError();                                                                                            \
		} while(false)
#else
	#define ALCall(func) func
#endif
