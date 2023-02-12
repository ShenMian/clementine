// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

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
	Sound() = default;

	Sound(const std::filesystem::path& path)
	{
		alGenBuffers(1, &handle);
		load(path);
	}

	virtual ~Sound() { alDeleteBuffers(1, &handle); }

	/**
	 * @brief 从文件加载声音.
	 *
	 * @param path 声音文件路径.
	 */
	void load(const std::filesystem::path& path)
	{
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

		const uint16_t bitsPerSample = (data.frameSize / data.channelCount) * 8;

		if(bitsPerSample == 8)
		{
			std::vector<uint8_t> buf(data.samples.size());
			std::ranges::transform(data.samples, buf.begin(),
			                       [](float x) { return static_cast<uint8_t>((x * 127.f) + 128.f); });
			load(buf.data(), buf.size(), data.sampleRate, data.channelCount, bitsPerSample);
		}
		else if(bitsPerSample == 16)
		{
			std::vector<int16_t> buf(data.samples.size());
			std::ranges::transform(data.samples, buf.begin(), [](float x) {
				return static_cast<int16_t>(x * std::numeric_limits<int16_t>::max());
			});
			load(buf.data(), buf.size() * sizeof(int16_t), data.sampleRate, data.channelCount, bitsPerSample);
		}
		else
			throw std::runtime_error("unknown sample size");
	}

	/**
	 * @brief 从内存加载声音.
	 *
	 * @param data          样本数据.
	 * @param size          数据大小, 单位: 字节.
	 * @param sampleRate    采样率.
	 * @param channels      通道数.
	 * @param bitsPerSample .
	 */
	void load(const void* data, size_t size, uint32_t sampleRate, uint16_t channelCount, uint16_t bitsPerSample)
	{
		this->samplesCount  = size / (bitsPerSample / 8);
		this->sampleRate    = sampleRate;
		this->channelCount  = channelCount;
		this->bitsPerSample = bitsPerSample;

		const auto format = GetALFormat(channelCount, bitsPerSample);
		if(!format.has_value())
			throw std::runtime_error("unknown audio format");
		alBufferData(handle, format.value(), data, static_cast<ALsizei>(size), sampleRate);
	}

	/**
	 * @brief 获取声音总长度, 单位: 秒.
	 */
	float getDuration() const { return (float)samplesCount / channelCount / sampleRate; }

	/**
	 * @brief 获取样本数.
	 */
	auto getSampleCount() const { return samplesCount / (bitsPerSample / 8); }

	/**
	 * @brief 获取通道数.
	 */
	auto getChannelCount() const noexcept { return channelCount; }

	/**
	 * @brief 获取 OpenAL 句柄.
	 */
	auto getHandle() const noexcept { return handle; }

private:
	uint32_t samplesCount  = 0;
	uint32_t sampleRate    = 0;
	uint16_t channelCount  = 0;
	uint16_t bitsPerSample = 0;

	unsigned int handle;
};

} // namespace audio
