// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "image_loader.h"
#include "manager.hpp"

namespace res
{

Image ImageLoader::load(const std::string& name, const std::filesystem::path& path)
{
	// TODO: 将资源登记到资源管理器中
	return Image(path);
}

} // namespace res
