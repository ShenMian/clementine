// Copyright 2020 SMS
// License(Apache-2.0)
// 目标平台

#ifndef CLEM_PLATFORM_H_
#define CLEM_PLATFORM_H_

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(__WIN32__) || defined(__MINGW32__) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
	#define OS_WIN
#endif

#if defined(TARGET_OS_IPHONE)
	#define OS_IPHONE
#endif

#if defined(TARGET_OS_MAC)
	#define OS_MAC
#endif

#if defined(__unix__) || defined(unix) || defined(__unix) || defined(OS_MAC)
	#define OS_UNIX
#endif

#if defined(__linux__) || defined(__linux)
	#define OS_LINUX
#endif

#if defined(ANDROID) || defined(_ANDROID_)
	#define OS_ANDROID
#endif

#ifdef OS_WIN
	#include <windows.h>
	#define hStdOut GetStdHandle(STD_OUTPUT_HANDLE)
#endif

#endif // CLEM_PLATFORM_H_
