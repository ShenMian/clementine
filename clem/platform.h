// Copyright 2020 SMS
// License(Apache-2.0)
// 目标平台

#ifndef CLEM_PLATFORM_H_
#define CLEM_PLATFORM_H_

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
	#define OS_WIN
#elif defined(__unix__) || defined(unix) || defined(__unix)
	#define OS_UNIX
#elif defined(__linux__) || defined(__linux)
	#define OS_LINUX
#elif defined(TARGET_OS_IPHONE)
	#define OS_IPHONE
#elif defined(TARGET_OS_MAC)
	#define OS_MAC
#elif defined(ANDROID) || defined(_ANDROID_)
	#define OS_ANDROID
#else
	#define OS_UNKNOWN
	#define OS_LINUX // TODO(SMS): 部分系统不存在相关宏, 有待更好解决方案
#endif

#ifdef OS_WIN
	#include <windows.h>
	#define hStdOut GetStdHandle(STD_OUTPUT_HANDLE)
#endif

#endif // CLEM_PLATFORM_H_
