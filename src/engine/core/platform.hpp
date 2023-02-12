// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

// OS

#define OS_UNKNOWN 0
#define OS_WIN     1
#define OS_LINUX   2
#define OS_MAC     3
#define OS_UNIX    4
#define OS_ANDROID 5
#define OS_IOS     6

#if defined(_WIN32)
	#define TARGET_OS OS_WIN
#elif defined(__unix__) || defined(unix) || defined(__unix)
	#define TARGET_OS OS_UNIX
#elif defined(__linux__) && !defined(__ANDROID__)
	#define TARGET_OS OS_LINUX
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE // TARGET_OS_IPHONE includes TARGET_OS_IOS TARGET_OS_TV and TARGET_OS_WATCH. see
	                     // TargetConditionals.h
		#define TARGET_OS OS_IOS
	#elif TARGET_OS_MAC
		#define TARGET_OS OS_MAC
	#endif
#elif defined(__ANDROID__)
	#define TARGET_OS OS_ANDROID
#else
	#define TARGET_OS OS_UNKNOWN
#endif

#if TARGET_OS == OS_UNKNOWN
	#error "The target platform is not supported"
#endif

#if TARGET_OS == OS_WIN
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#define _WIN32_WINDOWS 0x0A00 // Windows 10
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <windows.h>
	#undef near
	#undef far
#endif

// Compiler

#define COMPILER_UNKNOWN 0
#define COMPILER_MSVC    1
#define COMPILER_CLANG   2
#define COMPILER_GCC     3

#if defined(_MSC_VER)
	#define TARGET_COMPILER COMPILER_MSVC
#elif defined(__clang__)
	#define TARGET_COMPILER COMPILER_CLANG
#elif defined(__GNUC__)
	#define TARGET_COMPILER COMPILER_GCC
#else
	#define TARGET_COMPILER COMPILER_UNKNOWN
#endif

#ifdef __GNUC__
	#define GCC_VERSION_AT_LEAST(x, y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
	#define GCC_VERSION_AT_LEAST(x, y) 0
#endif

#if GCC_VERSION_AT_LEAST(3, 1)
	#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
	#define DEPRECATED __declspec(deprecated)
#else
	#define DEPRECATED
#endif

#if defined(_MSC_VER)
	#define DISABLE_WARNING_PUSH           __pragma(warning(push))
	#define DISABLE_WARNING_POP            __pragma(warning(pop))
	#define DISABLE_WARNING(warningNumber) __pragma(warning(disable : warningNumber))
#elif defined(__GNUC__) || defined(__clang__)
	#define DO_PRAGMA(X)                 _Pragma(#X)
	#define DISABLE_WARNING_PUSH         DO_PRAGMA(GCC diagnostic push)
	#define DISABLE_WARNING_POP          DO_PRAGMA(GCC diagnostic pop)
	#define DISABLE_WARNING(warningName) DO_PRAGMA(GCC diagnostic ignored #warningName)
#else
	#define DISABLE_WARNING_PUSH
	#define DISABLE_WARNING_POP
	#define DISABLE_WARNING(warningName)
#endif
