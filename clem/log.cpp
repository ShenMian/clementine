// Copyright 2020 SMS
// License(Apache-2.0)
// 日志

#include "log.h"
#include <ctime>
#include <cassert>
#include <iostream>

using std::map;
using std::string;
using std::ofstream;

ofstream Log::file;

ofstream& Log::info(const string& s)
{
	file << "[INFO] " << s << std::endl;
	return file;
}

std::ofstream& Log::warn(const string& s)
{
	file << "[WARN] " << s << std::endl;
	return file;
}

std::ofstream& Log::error(const string& s)
{
	file << "[ERROR] " << s << std::endl;
	return file;
}

std::ofstream& Log::fatal(const string& s)
{
	file << "[FATAL] " << s << std::endl;
	return file;
}
