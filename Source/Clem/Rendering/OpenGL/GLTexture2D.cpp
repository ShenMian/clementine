// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLTexture2D.h"
#include "Clem/Assert.h"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <type_traits>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace fs = std::filesystem;

namespace clem
{

static_assert(std::is_same<GLTexture2D::id_type, GLuint>::value);

GLTexture2D::GLTexture2D(const fs::path& path)
{
	CLEM_ASSERT_TRUE(fs::exists(path), "texture file doesn't exist");

	int height, width, channels;
	auto data = loadFromFile(path, height, width, channels);

	GLenum internalFormat, dataFormat;
	switch(channels)
	{
	case 3:
		internalFormat = GL_RGB8;
		dataFormat     = GL_RGB;
		break;

	case 4:
		internalFormat = GL_RGBA8;
		dataFormat     = GL_RGBA;
		break;

	default:
		assert(false);
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &handle);
	glTextureStorage2D(handle, 1, internalFormat, width, height);

	glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

	assert(glGetError() == GL_NO_ERROR);

	stbi_image_free(data);
}

GLTexture2D::~GLTexture2D()
{
	glDeleteTextures(1, &handle);
}

void GLTexture2D::bind(id_type slot)
{
	glBindTextureUnit(slot, handle);
}

void* GLTexture2D::nativeHandle()
{
	return &handle;
}

void* GLTexture2D::loadFromFile(const std::filesystem::path& path, int& width, int& height, int& channels)
{
	auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
	assert(data);

	return data;
}

} // namespace clem