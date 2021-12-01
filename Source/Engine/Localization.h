// Copyright 2021 ShenMian
// License(Apache-2.0)

#include <filesystem>
#include <unordered_map>

class Localization
{
public:
	static const std::string& str(const std::string& key);
	static const char* cstr(const std::string& key);

	static void load(const std::filesystem::path& path);

private:
	static std::unordered_map<std::string, std::string> dict;
};

using loc = Localization;
