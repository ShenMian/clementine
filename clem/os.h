// Copyright 2020 SMS
// License(Apache-2.0)
// 编译时系统信息

#ifndef CLEM_OS_H_
#define CLEM_OS_H_

// 定义操作系统宏, 用于判断操作系统类型
#ifdef _WIN32
	#define OS_WIN // Windows
	#ifdef _WIN64
		#define OS_WIN_64
	#else
		#define OS_WIN_32
	#endif
#else
	#if defined(__unix__) || defined(unix)
		#define OS_UNIX
	#endif

	#define OS_LINUX // Linux
#endif

#ifdef OS_WIN
	#include <windows.h>
	#define hStdOut GetStdHandle(STD_OUTPUT_HANDLE)
#endif

#endif // CLEM_OS_H_
