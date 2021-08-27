// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(__WIN32__) || defined(__MINGW32__) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#    define OS_WIN
#elif defined(__unix__) || defined(unix) || defined(__unix)
#    define OS_UNIX
#elif defined(__linux__) || defined(__linux)
#    define OS_LINUX
#elif defined(ANDROID) || defined(_ANDROID_)
#    define OS_ANDROID
#elif define(__APPLE__)
#    include <TargetConditionals.h>
#else
#    error Platform not supported.
#endif

#if defined(TARGET_OS_MAC)
#    define OS_MAC
#    define OS_UNIX
#endif

#ifdef OS_WIN
#    define WIN32_LEAN_AND_MEAN
#    define NOMINMAX

#    define _WIN32_WINDOWS 0x0A00 // Windows 10
#    define _WINSOCK_DEPRECATED_NO_WARNINGS
#    include <windows.h>
#endif

#if !defined(OS_UNIX) && !defined(OS_WIN)
#    error This platform is not supported.
#endif

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x, y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x, y) 0
#endif

#if GCC_VERSION_AT_LEAST(3, 1)
#    define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define DEPRECATED __declspec(deprecated)
#else
#    define DEPRECATED
#endif

#if defined(_MSC_VER)
#    define DISABLE_WARNING_PUSH           __pragma(warning(push))
#    define DISABLE_WARNING_POP            __pragma(warning(pop))
#    define DISABLE_WARNING(warningNumber) __pragma(warning(disable : warningNumber))
#elif defined(__GNUC__) || defined(__clang__)
#    define DO_PRAGMA(X)                 _Pragma(#    X)
#    define DISABLE_WARNING_PUSH         DO_PRAGMA(GCC diagnostic push)
#    define DISABLE_WARNING_POP          DO_PRAGMA(GCC diagnostic pop)
#    define DISABLE_WARNING(warningName) DO_PRAGMA(GCC diagnostic ignored #    warningName)
#else
#    define DISABLE_WARNING_PUSH
#    define DISABLE_WARNING_POP
#    define DISABLE_WARNING(warningName)
#endif
