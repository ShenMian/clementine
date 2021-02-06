// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#include "logger.h"
#include <cassert>
#include <ctime>

using std::map;
using std::string;
using std::ofstream;

Logger Log;

map<short, ofstream> Logger::index;

ofstream& Logger::info(const string& msg)
{
	assert(index[0].is_open());
	index[0] << "[INFO] " << msg;
	return index[0];
}

void Logger::write(short id, Level level, const string msg)
{
	string buf;
	
	/*
	time_t systemTime = std::time(NULL);
	tm*    localTime  = std::localtime(&systemTime);
	printf("local time is: %s\n", asctime(localTime));
	*/

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

	index.at(id) << buf << std::endl;
}

void Logger::add(short id, const string path)
{
	index.emplace(id, path);
}

void Logger::remove(short id)
{
	index.erase(id);
}
