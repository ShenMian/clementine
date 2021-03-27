// Copyright 2021 SMS
// License(Apache-2.0)

#include "Log.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace spdlog;

static std::shared_ptr<logger> coreLogger;

void Log::init()
{
	try
	{
		coreLogger = rotating_logger_mt("engine", "logs/clem.log", 1024 * 1024 * 5, 3);
	}
	catch(const spdlog_ex& e)
	{
		printf("Logger init failed: %s", e.what());
		assert(false);
	}

	coreLogger->set_pattern("[%D %T][thread %t][%L] %n : %v.");
	flush_every(std::chrono::seconds(1));
}

std::shared_ptr<logger> Log::getLogger()
{
	assert(coreLogger != nullptr);
	return coreLogger;
}