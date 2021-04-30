// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Assert.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace clem
{

#define LOG_LEVEL_INFO  0
#define LOG_LEVEL_WARN  1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_FATAL 3

#ifndef LOG_AVTIVE_LEVEL
#	define LOG_AVTIVE_LEVEL LOG_LEVEL_INFO /// 要记录的最低日志等级, 默认值为 LOG_LEVEL_INFO
#endif

static_assert(LOG_LEVEL_INFO <= LOG_AVTIVE_LEVEL && LOG_AVTIVE_LEVEL <= LOG_LEVEL_FATAL);

/**
 * @brief 日志记录器.
 */
class Logger
{
public:
	Logger(const std::string& name);

	/**
	 * @brief 一般消息.
	 * 
	 * @param fmt  格式字符串.
	 * @param args 参数.
	 */
	template <typename FmtStr, typename... Args>
	void info(const FmtStr& fmt, Args&&... args);

	/**
	 * @brief 警告消息.
	 * 
	 * @param fmt  格式字符串.
	 * @param args 参数.
	 */
	template <typename FmtStr, typename... Args>
	void warn(const FmtStr& fmt, Args&&... args);

	/**
	 * @brief 错误消息.
	 * 
	 * @param fmt  格式字符串.
	 * @param args 参数.
	 */
	template <typename FmtStr, typename... Args>
	void error(const FmtStr& fmt, Args&&... args);

	/**
	 * @brief 致命错误消息. 调用后会终止程序.
	 * 
	 * @param fmt  格式字符串.
	 * @param args 参数.
	 */
	template <typename FmtStr, typename... Args>
	void fatal(const FmtStr& fmt, Args&&... args);

	static void    create(const std::string& name);
	static Logger& get(const std::string& name);

private:
	std::shared_ptr<spdlog::logger> logger;
	
	static std::unordered_map<std::string, Logger> loggers;
};

template <typename FmtStr, typename... Args>
void Logger::info(const FmtStr& fmt, Args&&... args)
{
#if LOG_LEVEL_INFO >= LOG_AVTIVE_LEVEL
	logger->info(fmt, std::forward<Args>(args)...);
#endif
}

template <typename FmtStr, typename... Args>
void Logger::warn(const FmtStr& fmt, Args&&... args)
{
#if LOG_LEVEL_WARN >= LOG_AVTIVE_LEVEL
	logger->warn(fmt, std::forward<Args>(args)...);
#endif
}

template <typename FmtStr, typename... Args>
void Logger::error(const FmtStr& fmt, Args&&... args)
{
#if LOG_LEVEL_ERROR >= LOG_AVTIVE_LEVEL
	logger->error(fmt, std::forward<Args>(args)...);
#endif
}

template <typename FmtStr, typename... Args>
void Logger::fatal(const FmtStr& fmt, Args&&... args)
{
#if LOG_LEVEL_FATAL >= LOG_AVTIVE_LEVEL
	logger->critical(fmt, std::forward<Args>(args)...);
#endif
	abort();
}

} // namespace clem

#define CLEM_LOG_INFO(name, ...)  clem::Logger::get(name).info(__VA_ARGS__)
#define CLEM_LOG_WARN(name, ...)  clem::Logger::get(name).warn(__VA_ARGS__)
#define CLEM_LOG_ERROR(name, ...) clem::Logger::get(name).error(__VA_ARGS__)
#define CLEM_LOG_FATAL(name, ...) clem::Logger::get(name).fatal(__VA_ARGS__)
