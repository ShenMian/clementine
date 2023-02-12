// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <filesystem>

namespace res
{

class Resource
{
public:
	const auto& name() const noexcept { return name_; }
	const auto& path() const noexcept { return path_; }

	bool operator==(const Resource& rhs) const noexcept { return path_ == rhs.path_; }

private:
	std::string           name_;
	std::filesystem::path path_;
};

} // namespace res
