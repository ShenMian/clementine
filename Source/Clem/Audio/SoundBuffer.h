// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <filesystem>
#include <vector>
#include <cstring>

namespace clem
{
/**
 * @addtogroup Audio
 * @{
 */

class SoundBuffer
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	SoundBuffer();

	~SoundBuffer();

	/**
	 * @brief 从文件加载声音.
	 *
	 * @param path 声音文件路径.
	 */
	bool loadFromFile(const std::filesystem::path& path);

	const uint8_t* getSamples() const;

	size_t getSampleCount() const;

private:
	std::vector<uint8_t> samples;
	int32_t              sampleRate;
	int16_t              channelCount;
	unsigned int         id; // OpenAL 缓冲区 ID

	int frequency;
	int format;

	/**
	 * 从 WAV 文件载入声音.
	 *
	 * @param path 文件路径.
	 */
	bool loadWavFile(const std::filesystem::path& path);
};

/**
* end of Audio group
* @}
*/

} // namespace clem
