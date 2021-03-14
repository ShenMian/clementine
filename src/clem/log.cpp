// Copyright 2021 SMS
// License(Apache-2.0)

#include "log.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace spdlog;

std::shared_ptr<spdlog::logger> Log::logger;

void Log::init()
{
	set_pattern("[%T][%=8l] %n: %v");
	try
	{
		logger = rotating_logger_mt("engine", "logs/clem.log", 1024 * 1024 * 5, 3);
	}
	catch(const spdlog_ex& e)
	{
		assert(false);
	}

	logger->set_level(level::trace);
}

std::shared_ptr<spdlog::logger> Log::getLogger()
{
	return logger;
}
