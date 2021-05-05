// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <filesystem>

namespace clem
{
/**
 * @addtogroup Audio
 * @{
 */

/**
 * @brief 声音.
 * 提前将音频文件载入到内存中, 作为声音效果. 适用于较小的音频文件.
 */
class Sound
{
public:
	typedef ALuint id_t;

	/**
	 * @brief 默认构造函数.
	 */
	Sound();

	/**
	 * @brief 构造函数, 从文件导入声音.
	 */
	Sound(const std::filesystem::path&);

	/**
	 * @brief 析构函数, 卸载声音.
	 */
	~Sound();

	/**
	 * @brief 加载声音.
	 *
	 * @param path 声音文件路径.
	 */
	void loadFromFile(const std::filesystem::path&);

	operator id_t() const;

private:
	/**
	 * 从 WAV 文件载入声音.
	 *
	 * @param path   文件路径
	 * @param format 格式
	 * @param data   声音数据缓冲区
	 * @param size   声音数据缓冲区大小
	 * @param freq   声音频率
	 */
	static void loadWavFile(const std::filesystem::path& path, ALenum& format, unsigned char*& data, ALsizei& size, ALsizei& freq);

	id_t id;
};

/**
 * end of Audio group
 * @}
 */
} // namespace clem
