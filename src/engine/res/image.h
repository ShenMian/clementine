// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <filesystem>
#include <math/math.hpp>
#include <span>
#include <vector>

namespace res
{

class Image
{
public:
	/**
	 * @brief 构造函数, 从文件载入图像.
	 *
	 * @see load
	 */
	Image(const std::filesystem::path& path) { load(path); }

	/**
	 * @brief 构造函数, 从内存载入图像.
	 *
	 * @see load
	 */
	Image(std::span<uint8_t> data, const Vector2i& size, int channels) { load(data, size, channels); }

	/**
	 * @brief 从文件载入图像.
	 *
	 * @param path 图像文件地址.
	 */
	void load(const std::filesystem::path& path);

	/**
	 * @brief 从内存载入图像.
	 *
	 * @param data      图像内存地址.
	 * @param sizeBytes 图像数据大小, 单位: 字节.
	 * @param size      图像尺寸.
	 * @param channels  通道数.
	 */
	void load(std::span<uint8_t> data, const Vector2i& size, int channels);

	/**
	 * @brief 导出图像到文件.
	 *
	 * @param path 图像文件地址.
	 *
	 * @note 保存 jpg 格式文件时使用的质量为 90.
	 */
	void save(const std::filesystem::path& path);

	/**
	 * @brief 获取数据.
	 */
	const uint8_t* data() const noexcept { return data_.data(); }

	/**
	 * @brief 获取分辨率.
	 */
	const auto& size() const noexcept { return size_; }

	/**
	 * @brief 获取大小.
	 */
	size_t size_bytes() const noexcept { return data_.size(); }

	/**
	 * @brief 获取通道数.
	 */
	auto channels() const noexcept { return channels_; }

	/**
	 * @brief 水平(左右)翻转.
	 */
	void flipHorizontally() noexcept
	{
		const auto rowSize = size_.x * channels_;

		for(size_t y = 0; y < size_.y; y++)
		{
			auto left  = data_.begin() + y * rowSize;
			auto right = data_.begin() + (y + 1) * rowSize - channels_;

			for(size_t x = 0; x < size_.x / 2; x++)
			{
				std::swap_ranges(left, left + channels_, right);
				left += channels_;
				right -= channels_;
			}
		}
	}

	/**
	 * @brief 垂直(上下)翻转.
	 */
	void flipVertically() noexcept
	{
		const auto rowSize = size_.x * channels_;

		auto top    = data_.begin();
		auto bottom = data_.end() - rowSize;

		for(size_t y = 0; y < size_.y / 2; y++)
		{
			std::swap_ranges(top, top + rowSize, bottom);
			top += rowSize;
			bottom -= rowSize;
		}
	}

private:
	std::vector<uint8_t> data_;
	Vector2i             size_;
	uint8_t              channels_;
};

} // namespace res
