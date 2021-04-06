// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(__WIN32__) || defined(__MINGW32__) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#	define OS_WIN
#endif

#if defined(__unix__) || defined(unix) || defined(__unix)
#	define OS_UNIX
#endif

#if defined(__linux__) || defined(__linux)
#	define OS_LINUX
#endif

#if defined(ANDROID) || defined(_ANDROID_)
#	define OS_ANDROID
#endif

#ifdef __APPLE__
#	include <TargetConditionals.h>
#endif

#if defined(TARGET_OS_MAC)
#	define OS_MAC
#	define OS_UNIX
#endif

#ifdef OS_WIN
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <windows.h>
#endif

#if !defined(OS_UNIX) && !defined(OS_WIN)
#	error This platform is not supported.
#endif

#ifdef __GNUC__
#	define GCC_VERSION_AT_LEAST(x, y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#	define GCC_VERSION_AT_LEAST(x, y) 0
#endif

#if GCC_VERSION_AT_LEAST(3, 1)
#	define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#	define DEPRECATED __declspec(deprecated)
#else
#	define DEPRECATED
#endif
