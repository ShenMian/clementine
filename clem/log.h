// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#ifndef CLEM_LOGGER_H_
#define CLEM_LOGGER_H_

#include <map>
#include <string>
#include <fstream>

enum class Level;

#define LOG_INFO Log::write(Level::info, __FILE__, __FUNCTION__, __LINE__)

class Log
{
public:
	static std::ofstream& info(const std::string&);
	static std::ofstream& warn(const std::string&);
	static std::ofstream& error(const std::string&);
	static std::ofstream& fatal(const std::string&);

	static void write(Level, const char* filename, const char* funcition, size_t line);

private:
	static std::ofstream file;
};

enum class Level
{
	info,
	warn,
	error,
	fatal
};

#endif // !CLEM_LOGGER_H_
