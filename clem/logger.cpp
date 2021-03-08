// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#include "logger.h"
#include <ctime>
#include <cassert>
#include <iostream>

using std::map;
using std::string;
using std::ofstream;

ofstream Log::file;

ofstream& Log::info(const string& msg)
{
	file << "[INFO] " << msg << std::endl;
	return file;
}

std::ofstream& Log::warn(const std::string&)
{
	return file;
}

std::ofstream& Log::error(const std::string&)
{
	return file;
}

std::ofstream& Log::fatal(const std::string&)
{
	return file;
}

void Log::write(Level level, const char* filename, const char* func, size_t line)
{
	string buf;
	
	time_t systemTime = std::time(NULL);
	tm*    localTime  = std::localtime(&systemTime);
	printf("local time is: %s\n", asctime(localTime));

	switch(level)
	{
	case Level::info:
		buf += "[INFO]";
		break;

	case Level::warn:
		buf += "[WARN]";
		break;

	case Level::error:
		buf += "[ERROR]";
		break;

	case Level::fatal:
		buf += "[FATAL]";
		break;

	default:
		assert(false);
	}
}
