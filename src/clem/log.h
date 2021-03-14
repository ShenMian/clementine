// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_LOG_H_
#define CLEM_LOG_H_

#include "spdlog/spdlog.h"

class Log
{
public:
	static void init();
	static std::shared_ptr<spdlog::logger> getLogger();

private:
	static std::shared_ptr<spdlog::logger> engineLogger;
};

#define CLEM_ENGINE_TRACE(...)    Log::getLogger()->trace(__VA_ARGS__)
#define CLEM_ENGINE_INFO(...)     Log::getLogger()->info(__VA_ARGS__)
#define CLEM_ENGINE_WARN(...)     Log::getLogger()->warn(__VA_ARGS__)
#define CLEM_ENGINE_ERROR(...)    Log::getLogger()->error(__VA_ARGS__)
#define CLEM_ENGINE_CRITICAL(...) Log::getLogger()->critical(__VA_ARGS__)

#endif // !CLEM_LOG_H_
