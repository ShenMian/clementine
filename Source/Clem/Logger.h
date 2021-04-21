// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Assert.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace clem
{

constexpr int log_level_trace = 0;
constexpr int log_level_debug = 1;
constexpr int log_level_info  = 2;
constexpr int log_level_warn  = 3;
constexpr int log_level_error = 4;
constexpr int log_level_fatal = 5;

constexpr int log_active_level = 1;

static_assert(log_level_trace <= log_active_level && log_active_level <= log_level_fatal);

/**
 * @brief 日志记录器.
 */
class Logger
{
public:
	Logger(const std::string& name);

	template <typename FormatString, typename... Args>
	void info(const FormatString& fmt, Args&&... args);

	template <typename FormatString, typename... Args>
	void warn(const FormatString& fmt, Args&&... args);

	template <typename FormatString, typename... Args>
	void error(const FormatString& fmt, Args&&... args);

	template <typename FormatString, typename... Args>
	void fatal(const FormatString& fmt, Args&&... args);

	static void    create(const std::string& name);
	static Logger& get(const std::string& name);

private:
	std::shared_ptr<spdlog::logger> logger;
	
	static std::unordered_map<std::string, Logger> loggers;
};

template <typename FormatString, typename... Args>
void Logger::info(const FormatString& fmt, Args&&... args)
{
	logger->info(fmt, std::forward<Args>(args)...);
}

template <typename FormatString, typename... Args>
void Logger::warn(const FormatString& fmt, Args&&... args)
{
	logger->warn(fmt, std::forward<Args>(args)...);
}

template <typename FormatString, typename... Args>
void Logger::error(const FormatString& fmt, Args&&... args)
{
	logger->error(fmt, std::forward<Args>(args)...);
}

template <typename FormatString, typename... Args>
void Logger::fatal(const FormatString& fmt, Args&&... args)
{
	logger->critical(fmt, std::forward<Args>(args)...);
	abort();
}

#define CLEM_LOG_INFO(name, ...)  Logger::get(name).info(__VA_ARGS__)
#define CLEM_LOG_WARN(name, ...)  Logger::get(name).warn(__VA_ARGS__)
#define CLEM_LOG_ERROR(name, ...) Logger::get(name).error(__VA_ARGS__)
#define CLEM_LOG_FATAL(name, ...) Logger::get(name).fatal(__VA_ARGS__)

} // namespace clem
