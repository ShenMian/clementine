// Copyright 2020 SMS
// License(Apache-2.0)
// Windows

#ifndef CLEM_WINDOWS_H_
#define CLEM_WINDOWS_H_

#include "platform.h"

#ifdef OS_WIN

class Windows
{
public:
	static void   initialize();
	static HANDLE getStdOut();

private:
	static HANDLE hStdOut;
};

#endif // OS_WIN

#endif // CLEM_WINDOWS_H_

