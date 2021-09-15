// Copyright 2021 SMS
// License(Apache-2.0)

#include "Logger.h"
#include "Core/Assert.hpp"
#include "FileLogger.h"

namespace clem
{

std::unordered_map<std::string, std::shared_ptr<Logger>> Logger::loggers;

Logger::Logger(std::string_view name)
    : name(name)
{
}

void Logger::add(std::shared_ptr<Logger> logger)
{
    Assert::isTrue(!loggers.contains(logger->getName()), std::format("logger '{}' already exist", logger->getName()));
    loggers.emplace(logger->getName(), logger);
}

void Logger::remove(const std::string& name)
{
    Assert::isTrue(loggers.contains(name), std::format("logger '{}' doesn't exist", name));
    loggers.erase(name);
}

std::shared_ptr<Logger> Logger::get(const std::string& name)
{
    Assert::isTrue(loggers.contains(name), std::format("logger '{}' doesn't exist", name));
    return loggers.find(name)->second;
}

void Logger::flushAll()
{
    for(const auto& pair : loggers)
        pair.second->flush();
}

void Logger::init()
{
    Logger::add(std::make_shared<FileLogger>("core", "logs/core.log"));
    Logger::add(std::make_shared<FileLogger>("audio", "logs/audio.log"));
    Logger::add(std::make_shared<FileLogger>("assert", "logs/assert.log"));
    Logger::add(std::make_shared<FileLogger>("render", "logs/render.log"));
    Logger::add(std::make_shared<FileLogger>("network", "logs/network.log"));
}

void Logger::deinit()
{
    flushAll();
    loggers.clear();
}

const std::string& Logger::getName() const
{
    return name;
}

/*
std::vector<spdlog::sink_ptr> sinks;
sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
sinks.back()->set_pattern("[%-7n][thread %t][%^%L%$] %v. - %oms");
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
*/

} // namespace clem