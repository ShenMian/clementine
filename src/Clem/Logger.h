// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "spdlog/spdlog.h"
#include <memory>

/**
 * ÈÕÖ¾¼ÇÂ¼Æ÷.
 */
class Logger
{
public:
	template <typename T>
	void info(const T& msg);

	template <typename T>
	void warn(const T& msg);

	template <typename T>
	void error(const T& msg);

	template <typename T>
	void fatal(const T& msg);

private:
	std::shared_ptr<spdlog::logger> spdlogger;
};

template<typename T>
void Logger::info(const T& msg)
{	
	spdlogger->info(msg);
}

template <typename T>
void Logger::warn(const T& msg)
{
	spdlogger->warn(msg);
}

template <typename T>
void Logger::error(const T& msg)
{
	spdlogger->error(msg);
}

template <typename T>
void Logger::fatal(const T& msg)
{
	spdlogger->critical(msg);
}
