// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <filesystem>
#include <memory>

namespace clem
{

class Texture2D
{
public:
	static std::shared_ptr<Texture2D> create(const std::filesystem::path& path);

	virtual void  bind(unsigned int slot) = 0;
	virtual void* nativeHandle()          = 0;
};

} // namespace clem
