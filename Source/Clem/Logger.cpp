// Copyright 2021 SMS
// License(Apache-2.0)

#include "Logger.h"
#include "Assert.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

using std::string;

namespace clem
{
std::unordered_map<std::string, Logger> Logger::loggers;

Logger::Logger(const string& name)
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + name + ".log"));
    sinks.back()->set_pattern("[%D %T][thread %t][%L] %v.");

    try
    {
        logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
    }
    catch(const spdlog::spdlog_ex& e)
    {
        printf("Logger init failed: %s", e.what());
        abort();
    }

    logger->info("------------------------------------");
}

void Logger::create(const string& name)
{
    loggers.emplace(name, name);
}

Logger& Logger::get(const string& name)
{
    auto res = loggers.find(name);
    Assert::isTrue(res != loggers.end(), std::format("logger named '{}' doesn't exist", name));
    return res->second;
}
} // namespace clem