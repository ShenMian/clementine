// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#ifndef CLEM_LOGGER_H_
#define CLEM_LOGGER_H_

#include <map>
#include <string>
#include <fstream>

/// 日志
class Log
{
public:
	enum class Level;

	static std::ofstream& info(const std::string&);
	static std::ofstream& warn(const std::string&);
	static std::ofstream& error(const std::string&);
	static std::ofstream& fatal(const std::string&);

private:
	static std::ofstream file;
};

enum class Log::Level
{
	info,
	warn,
	error,
	fatal
};

#endif // !CLEM_LOGGER_H_
