// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_LOG_H_
#define CLEM_LOG_H_

#include <cassert>
#include <memory>

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#pragma warning(pop)

constexpr int log_active_level = 1;

constexpr int log_level_trace = 0;
constexpr int log_level_debug = 1;
constexpr int log_level_info  = 2;
constexpr int log_level_warn  = 3;
constexpr int log_level_error = 4;
constexpr int log_level_fatal = 5;

class Log
{
public:
	enum class Level;

	static std::shared_ptr<spdlog::logger> getLogger();

	static void init();
	static void deinit();
};

enum class Log::Level
{
	trace,
	debug,
	info,
	warn,
	error,
	fatal
};

#define CLEM_CORE_TRACE(...) Log::getLogger()->trace(__VA_ARGS__)
#define CLEM_CORE_INFO(...)  Log::getLogger()->info(__VA_ARGS__)
#define CLEM_CORE_WARN(...)  Log::getLogger()->warn(__VA_ARGS__)
#define CLEM_CORE_ERROR(...) Log::getLogger()->error(__VA_ARGS__)
#define CLEM_CORE_FATAL(...)                 \
	do                                         \
	{                                          \
		Log::getLogger()->critical(__VA_ARGS__); \
		assert(false);                           \
	} while(0)

#endif // !CLEM_LOG_H_
