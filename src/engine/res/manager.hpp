// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "resource.hpp"
#include <filesystem>
#include <unordered_map>

namespace res
{

class Manager
{
public:
	static Manager& get_instance() noexcept
	{
		static Manager manager;
		return manager;
	}

private:
	std::unordered_map<uint32_t, Resource> resources;
};

} // namespace res
