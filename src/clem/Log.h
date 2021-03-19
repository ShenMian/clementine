// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_LOG_H_
#define CLEM_LOG_H_

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#pragma warning(pop)

#include <cassert>

class Log
{
public:
	static void init();
	static std::shared_ptr<spdlog::logger> getLogger();

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
};

#define CLEM_CORE_TRACE(...) Log::getLogger()->trace(__VA_ARGS__)
#define CLEM_CORE_INFO(...)  Log::getLogger()->info(__VA_ARGS__)
#define CLEM_CORE_WARN(...)  Log::getLogger()->warn(__VA_ARGS__)
#define CLEM_CORE_ERROR(...) Log::getLogger()->error(__VA_ARGS__)
#define CLEM_CORE_CRITICAL(...)              \
	do                                         \
	{                                          \
		Log::getLogger()->critical(__VA_ARGS__); \
		assert(!##__VA_ARGS__);                  \
	} while(0)

#endif // !CLEM_LOG_H_
