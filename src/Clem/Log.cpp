// Copyright 2021 SMS
// License(Apache-2.0)

#include "Log.h"
#include "Clem/Profiler.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace spdlog;
using namespace std;

static shared_ptr<logger> engineLogger;

static std::vector<logger> loggers;
static auto                sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/core.log", true);

void Log::init()
{
	PROFILE_FUNC();

	try
	{
		loggers.emplace_back("core", sink);
		loggers.back().set_pattern("[%D %T][thread %t][%L] %v.");
	}
	catch(const spdlog_ex& e)
	{
		printf("Logger init failed: %s", e.what());
		abort();
	}

	try
	{
		engineLogger = rotating_logger_mt("engine", "logs/clem.log", 1024 * 1024 * 5, 3);
	}
	catch(const spdlog_ex& e)
	{
		printf("Logger init failed: %s", e.what());
		assert(false);
	}

	engineLogger->set_pattern("[%D %T][thread %t][%L] %n : %v.");
	flush_every(std::chrono::seconds(1));

	CLEM_LOG_INFO("core", "log init");
}

void Log::deinit()
{
	PROFILE_FUNC();
	CLEM_LOG_INFO("core", "log deinit");

	engineLogger->flush();
}

shared_ptr<logger> Log::getLogger()
{
	assert(engineLogger != nullptr);
	return engineLogger;
}
