// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "image.h"
#include <filesystem>
#include <span>

namespace res
{

class ImageLoader
{
public:
	Image load(const std::string& name, const std::filesystem::path& path);
};

} // namespace res
