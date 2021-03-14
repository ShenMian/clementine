// Copyright 2021 SMS
// License(Apache-2.0)

#include "log.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <chrono>

using namespace spdlog;

std::shared_ptr<logger> Log::engineLogger;

void Log::init()
{
	try
	{
		engineLogger = rotating_logger_mt("engine", "logs/clem.log", 1024 * 1024 * 5, 3);
	}
	catch(const spdlog_ex& e)
	{
		assert(false);
	}

	engineLogger->set_pattern("[%T][%=8l] %n: %v");
	engineLogger->flush_on(level::err);

	flush_every(std::chrono::seconds(5));
}

std::shared_ptr<logger> Log::getLogger()
{
	assert(engineLogger != nullptr);
	return engineLogger;
}
