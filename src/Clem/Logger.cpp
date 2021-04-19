// Copyright 2021 SMS
// License(Apache-2.0)

#include "Logger.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

using std::string;

namespace clem
{

Logger::Logger(const string& name)
{
	try
	{
		spdlogger = spdlog::basic_logger_mt(name, "logs/" + name + ".txt");
		spdlogger->set_pattern("[%D %T][thread %t][%L] %v.");
	}
	catch(const spdlog::spdlog_ex& e)
	{
		printf("Logger init failed: %s", e.what());
		abort();
	}
}

} // namespace clem