// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include <filesystem>

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
	Sound(const std::filesystem::path& path);
	virtual ~Sound();

	/**
	 * @brief 从文件加载声音.
	 *
	 * @param path 声音文件路径.
	 */
	void loadFromFile(const std::filesystem::path& path);

	/**
	 * @brief 从内存加载声音.
	 *
	 * @param data          样本数据.
	 * @param size          数据大小, 单位: 字节.
	 * @param sampleRate    采样率.
	 * @param channels      通道数.
	 * @param bitsPerSample .
	 */
	void loadFromMemory(const void* data, size_t size, uint32_t sampleRate, uint16_t channels, uint16_t bitsPerSample);

	/**
	 * @brief 获取声音总长度, 单位: 秒.
	 */
	float getDuration() const { return (float)samples.size() / channelCount / sampleRate; }

	/**
	 * @brief 获取样本.
	 */
	auto getSamples() const { return samples; }

	/**
	 * @brief 获取样本数.
	 */
	auto getSampleCount() const { return samples.size() / (bitsPerSample / 8); }

	/**
	 * @brief 获取通道数.
	 */
	auto getChannelCount() const { return channelCount; }

	/**
	 * @brief 获取 OpenAL 句柄.
	 */
	auto getHandle() const { return handle; }

private:
	std::vector<uint8_t> samples;
	uint32_t             sampleRate    = 0;
	uint16_t             channelCount  = 0;
	uint16_t             bitsPerSample = 0;

	unsigned int handle;
};

} // namespace audio
