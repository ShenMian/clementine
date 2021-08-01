// Copyright 2021 SMS
// License(Apache-2.0)

#include "Texture2D.h"
#include "OpenGL/GLTexture2D.h"
#include "Renderer.h"

namespace fs = std::filesystem;

namespace clem
{

std::shared_ptr<Texture2D> Texture2D::create(const fs::path& path)
{
	switch(Renderer::getAPI())
	{
		using enum Renderer::API;
	case OpenGL:
		return std::make_shared<GLTexture2D>(path);
	}
	return nullptr;
}

} // namespace clem