// Copyright 2021 SMS
// License(Apache-2.0)

#include "log.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <chrono>

using namespace spdlog;

std::shared_ptr<logger> Log::coreLogger;

void Log::init()
{
	try
	{
		coreLogger = rotating_logger_mt("engine", "logs/clem.log", 1024 * 1024 * 5, 3);
	}
	catch(const spdlog_ex& e)
	{
		assert(false);
	}

	coreLogger->set_pattern("[%T][%=8l] %n : %v.");
	coreLogger->flush_on(level::trace);
	coreLogger->flush_on(level::info);
	coreLogger->flush_on(level::warn);
	coreLogger->flush_on(level::err);
	coreLogger->flush_on(level::critical);

	// flush_every(std::chrono::seconds(1));
}

std::shared_ptr<logger> Log::getLogger()
{
	assert(coreLogger != nullptr);
	return coreLogger;
}
