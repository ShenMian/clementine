// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "image.h"
#include <filesystem>
#include <memory>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <fmt/std.h>

// TODO: 已在 graphics 中定义
// #ifndef STB_IMAGE_IMPLEMENTATION // 防止和其他第三方库内的 stb 重定义
// 	#define STB_IMAGE_IMPLEMENTATION
// #endif
#include <stb_image.h>

// #ifndef STB_IMAGE_WRITE_IMPLEMENTATION
// 	#define STB_IMAGE_WRITE_IMPLEMENTATION
// #endif
#include <stb_image_write.h>


namespace res
{

using StbiImage = std::unique_ptr<unsigned char, decltype([](auto data) { stbi_image_free(data); })>;

void Image::load(const std::filesystem::path& path)
{
	if(!std::filesystem::is_regular_file(path))
		throw std::runtime_error(fmt::format("no such file: {}", path));

	Vector2i  size;
	int       channels;
	StbiImage pixels(stbi_load(path.string().c_str(), &size.x, &size.y, &channels, 0));
	if(pixels == nullptr)
		throw std::runtime_error(fmt::format("failed load image from file: {}", path));

	load({pixels.get(), size.x * size.y * channels * sizeof(float)}, size, channels);
}

void Image::load(std::span<uint8_t> data, const Vector2i& size, int channels)
{
	data_.assign(data.begin(), data.end());
	size_     = size;
	channels_ = channels;
}

} // namespace res
