// Copyright 2022 SMS
// License(Apache-2.0)

#include <fmt/color.h>
#include <fmt/core.h>
#include <optional>
#include <string>
#include <unordered_map>

#pragma once

namespace core
{

/**
 * @brief 日志记录器.
 */
class Logger
{
public:
	Logger(const std::string& name) : name_(name) { loggers.insert({name, this}); }
	virtual ~Logger() = default;

	static Logger* get(const std::string& name)
	{
		auto it = loggers.find(name);
		if(it == loggers.end())
			return nullptr;
		return it->second;
	}

	virtual void info(std::string_view msg)  = 0;
	virtual void good(std::string_view msg)  = 0;
	virtual void error(std::string_view msg) = 0;
	virtual void warn(std::string_view msg)  = 0;
	virtual void flush()                     = 0;

protected:
	std::string name_;

private:
	inline static std::unordered_map<std::string, Logger*> loggers;
};

} // namespace core

#define CLEM_LOG_INFO(name, msg)  ::core::Logger::get(name)->info(msg)
#define CLEM_LOG_GOOD(name, msg)  ::core::Logger::get(name)->good(msg)
#define CLEM_LOG_ERROR(name, msg) ::core::Logger::get(name)->error(msg)
#define CLEM_LOG_WARN(name, msg)  ::core::Logger::get(name)->warn(msg)
