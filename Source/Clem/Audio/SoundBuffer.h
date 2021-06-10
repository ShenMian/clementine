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
	 * @brief Ĭ�Ϲ��캯��.
	 */
	SoundBuffer();

	~SoundBuffer();

	/**
	 * @brief ���ļ���������.
	 *
	 * @param path �����ļ�·��.
	 */
	bool loadFromFile(const std::filesystem::path& path);

	const uint8_t* getSamples() const;

	size_t getSampleCount() const;

private:
	std::vector<uint8_t> samples;
	int32_t              sampleRate;
	int16_t              channelCount;
	unsigned int         id; // OpenAL ������ ID

	int frequency;
	int format;

	/**
	 * �� WAV �ļ���������.
	 *
	 * @param path �ļ�·��.
	 */
	bool loadWavFile(const std::filesystem::path& path);
};

/**
* end of Audio group
* @}
*/

} // namespace clem
