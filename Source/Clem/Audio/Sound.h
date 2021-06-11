// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstring>
#include <filesystem>
#include <vector>

namespace clem
{
/**
 * @addtogroup Audio
 * @{
 */

class Sound
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	Sound();

	/**
	 * @brief 构造函数, 从文件导入声音.
	 */
	Sound(const std::filesystem::path& path);

	/**
	 * @brief 默认析构函数.
	 */
	~Sound();

	/**
	 * @brief 从文件加载声音.
	 *
	 * @param path 声音文件路径.
	 */
	void loadFromFile(const std::filesystem::path& path);

	const uint8_t* getSamples() const;

	size_t getSampleCount() const;

	int getBufferId() const;

private:
	std::vector<uint8_t> samples;
	int32_t              sampleRate   = 0;
	int16_t              channelCount = 0;
	unsigned int         bufferId;

	/**
	 * 从 WAV 文件载入声音.
	 *
	 * @param path 文件路径.
	 */
	void loadWavFile(const std::filesystem::path& path);
};

/**
* end of Audio group
* @}
*/
} // namespace clem
