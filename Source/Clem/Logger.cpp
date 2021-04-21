// Copyright 2021 SMS
// License(Apache-2.0)

#include "Logger.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

using std::string;

namespace clem
{

std::unordered_map<std::string, Logger> Logger::loggers;

Logger::Logger(const string& name)
{
	try
	{
		logger = spdlog::basic_logger_mt(name, "logs/" + name + ".log");
		logger->set_pattern("[%D %T][thread %t][%L] %v.");
	}
	catch(const spdlog::spdlog_ex& e)
	{
		printf("Logger init failed: %s", e.what());
		abort();
	}
}

void Logger::create(const string& name)
{
	loggers.emplace(name, name);
}

Logger& Logger::get(const string& name)
{
	auto res = loggers.find(name);
	ASSERT_TRUE(res != loggers.end(), "logger named '" + name + "' doesn't exist");
	return res->second;
}

} // namespace clem