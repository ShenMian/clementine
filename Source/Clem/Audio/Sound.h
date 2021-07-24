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
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Sound();

	/**
	 * @brief ���캯��, ���ļ���������.
	 */
	Sound(const std::filesystem::path& path);

	/**
	 * @brief Ĭ����������.
	 */
	~Sound();

	/**
	 * @brief ���ļ���������.
	 *
	 * @param path �����ļ�·��.
	 */
	void loadFromFile(const std::filesystem::path& path);

	const uint8_t* getSamples() const;
	size_t         getSampleCount() const;
	unsigned int   getSampleRate() const;
	unsigned int   getChannelCount() const;

	/**
	 * @brief ��ȡ������ʱ��.
	 *
	 * @return ������ʱ��, ��λ: ��.
	 */
	size_t getTime() const;

	int getBufferId() const;

private:
	std::vector<uint8_t> samples;
	int32_t              sampleRate;
	int16_t              channelCount;
	int16_t              bitsPerSample;
	unsigned int         bufferId;
	bool                 initialized = false;

	/**
	 * �� WAV �ļ���������.
	 *
	 * @param path �ļ�·��.
	 */
	void loadWavFile(const std::filesystem::path& path);
};

/**
* end of Audio group
* @}
*/
} // namespace clem
