// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <filesystem>

namespace res
{

class Loader
{
public:
	void load(const std::filesystem::path& path);

	template <typename T, typename... Args>
	T load(Args&&... args)
	{
		T resource = T{args...};
		return resource;
	}


private:
};

} // namespace res
