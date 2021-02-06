// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#ifndef CLEM_LOGGER_H_
#define CLEM_LOGGER_H_

#include <map>
#include <string>
#include <fstream>

enum class Level;

class Logger
{
public:
	static std::ofstream& info(const std::string&);
	static std::ofstream& warn(const std::string&);
	static std::ofstream& error(const std::string&);
	static std::ofstream& fatal(const std::string&);

	static void write(short id, Level, const std::string msg);

	static void add(short id, const std::string path);
	static void remove(short id);

private:
	static std::map<short, std::ofstream> index;
};

enum class Level
{
	info,
	warn,
	error,
	fatal
};

extern Logger Log;

#endif // !CLEM_LOGGER_H_
