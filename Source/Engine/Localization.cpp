// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Localization.h"
#include <cctype>
#include <cstdio>
#include <cassert>
#include <fstream>

namespace fs = std::filesystem;

namespace
{

std::string keyNotFound = "key not found";

}

std::unordered_map<std::string, std::string> Localization::dict;

const std::string& Localization::str(const std::string& key)
{
	if(dict.empty())
		return key;

	auto it = dict.find(key);
	if(it != dict.end())
		return it->second;
	else
		return keyNotFound;
}

const char* Localization::cstr(const std::string& key)
{
	return str(key).c_str();
}

void Localization::load(const fs::path& path)
{
	dict.clear();

	std::ifstream file(path);
	assert(file.is_open());

	std::string src;

	std::string line;
	while(std::getline(file, line))
	{
		if(line.empty() || line[0] == '#')
			continue;
		std::stringstream ss(line);
		std::string key, value;

		ss >> key >> value;
		value = line.substr(key.size());

		while(std::isspace(value.front()))
			value = value.substr(1);
		if((value.starts_with('\"') && value.ends_with('\"')) ||
			(value.starts_with('\'') && value.ends_with('\'')))
			value = value.substr(1, value.size() - 2);

		if(key == "src:")
			src = value;
		else if(key == "dst:")
			dict[src] = value;
		else
		{
			assert(false);
			return;
		}
	}
}
