// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/check.hpp"
#include <AL/al.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <libnyquist/Decoders.h>
#include <optional>
#include <stdexcept>

namespace
{

std::optional<ALenum> GetALFormat(int channelCount, int bitsPerSample)
{
	if(channelCount == 1)
	{
		if(bitsPerSample == 8)
			return AL_FORMAT_MONO8;
		if(bitsPerSample == 16)
			return AL_FORMAT_MONO16;
	}
	else if(channelCount == 2)
	{
		if(bitsPerSample == 8)
			return AL_FORMAT_STEREO8;
		if(bitsPerSample == 16)
			return AL_FORMAT_STEREO16;
	}
	return std::nullopt;
}

} // namespace

namespace audio
{

/**
 * @brief 声音.
 *
 * 音频数据缓冲区.
 */
class Sound
{
public:
	Sound() { alGenBuffers(1, &handle); };

	/**
	 * @brief 构造函数, 从文件载入音频.
	 *
	 * @see load
	 */
	Sound(const std::filesystem::path& path) : Sound() { load(path); }

	virtual ~Sound() { alDeleteBuffers(1, &handle); }

	/**
	 * @brief 从文件载入音频.
	 *
	 * @param path 声音文件路径.
	 */
	void load(const std::filesystem::path& path)
	{
		if(!std::filesystem::is_regular_file(path))
			throw std::runtime_error(fmt::format("no such file: {}", path));

		nqr::NyquistIO loader;
		if(!loader.IsFileSupported(path.string()))
			throw std::runtime_error("file format do not support");

		nqr::AudioData data;
		loader.Load(&data, path.string());

		// libnyquist 内部 BUG 临时解决方案
		if(data.frameSize == 32)
			data.frameSize = 4;
		else if(data.frameSize == 16)
			data.frameSize = 2;
		else
			data.frameSize = 4;

		const uint16_t bits_per_sample = (data.frameSize / data.channelCount) * 8;

		if(bits_per_sample == 8)
		{
			std::vector<uint8_t> buf(data.samples.size());
			std::ranges::transform(data.samples, buf.begin(),
			                       [](float x) { return static_cast<uint8_t>((x * 127.f) + 128.f); });
			load(buf.data(), buf.size() * sizeof(uint8_t), data.sampleRate, data.channelCount, bits_per_sample);
		}
		else if(bits_per_sample == 16)
		{
			std::vector<int16_t> buf(data.samples.size());
			std::ranges::transform(data.samples, buf.begin(), [](float x) {
				return static_cast<int16_t>(x * std::numeric_limits<int16_t>::max());
			});
			load(buf.data(), buf.size() * sizeof(int16_t), data.sampleRate, data.channelCount, bits_per_sample);
		}
		else
			throw std::runtime_error("unknown sample size");
	}

	/**
	 * @brief 从内存加载声音.
	 *
	 * @param data            样本数据.
	 * @param size            数据大小, 单位: 字节.
	 * @param sample_rate     采样率.
	 * @param channels        通道数.
	 * @param bits_per_sample 单个样本大小.
	 */
	void load(const void* data, size_t size, uint32_t sample_rate, uint16_t channels, uint16_t bits_per_sample)
	{
		debug_check(sample_rate_ > 0 && channels_ > 0);

		sample_count_    = size / (bits_per_sample / 8);
		sample_rate_     = sample_rate;
		channels_        = channels;
		bits_per_sample_ = bits_per_sample;

		const auto format = GetALFormat(channels, bits_per_sample);
		if(!format.has_value())
			throw std::runtime_error("unknown audio format");
		alBufferData(handle, format.value(), data, static_cast<ALsizei>(size), sample_rate);
	}

	/**
	 * @brief 获取声音总长度, 单位: 秒.
	 */
	auto get_duration() const noexcept { return (float)sample_count_ / channels_ / sample_rate_; }

	/**
	 * @brief 获取样本数.
	 */
	auto get_sample_count() const noexcept { return sample_count_ / (bits_per_sample_ / 8); }

	/**
	 * @brief 获取通道数.
	 */
	auto get_channel_count() const noexcept { return channels_; }

	/**
	 * @brief 获取 OpenAL 句柄.
	 */
	auto get_handle() const noexcept { return handle; }

private:
	uint32_t sample_count_    = 0;
	uint32_t sample_rate_     = 0;
	uint16_t channels_        = 0;
	uint16_t bits_per_sample_ = 0;

	unsigned int handle;
};

} // namespace audio
