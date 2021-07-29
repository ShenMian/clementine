// Copyright 2021 SMS
// License(Apache-2.0)

#include "Texture2D.h"
#include "OpenGL/GLTexture2D.h"

namespace fs = std::filesystem;

namespace clem
{

std::shared_ptr<Texture2D> Texture2D::create(const fs::path& path)
{
	return std::make_shared<GLTexture2D>(path);
}

} // namespace clem
